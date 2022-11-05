
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include "LineParser.h"
#include "procs.h"
#include <fcntl.h>


void execute(cmdLine *pCmdLine);
void cd(cmdLine *execCom, char ** directory);
void showProcs(process** proc);

int ** createPipes(int nPipes){
	int** pipes;
	pipes=(int**) calloc(nPipes, sizeof(int));
	for (int i=0; i<nPipes;i++){
		pipes[i]=(int*) calloc(2, sizeof(int));
		pipe(pipes[i]);
	}  
	return pipes;
}
void releasePipes(int **pipes, int nPipes){
	for (int i=0; i<nPipes;i++){
		free(pipes[i]);
	}  
	free(pipes);
}
int *leftPipe(int **pipes, cmdLine *pCmdLine){
	if (pCmdLine->idx == 0) return NULL;
	return pipes[pCmdLine->idx -1];
}

int *rightPipe(int **pipes, cmdLine *pCmdLine){
	if (pCmdLine->next == NULL) return NULL;
	return pipes[pCmdLine->idx];
}

void stop(int pid)
{
	kill(pid, SIGINT);
}
void nap(int time, int pid);
void nap(int time, int pid)
{
	kill(pid, SIGTSTP);
	sleep(time);
	kill(pid, SIGCONT);
}
void cd(cmdLine *execCom, char ** directory)
{
	if (execCom->argCount < 2)
	{
		chdir(getenv("HOME"));
		*directory ="~";
	}
	if (execCom->argCount == 2)
	{
        	if(chdir(execCom->arguments[1]) == -1)
			fprintf(stderr, "Error: not a valid directory\n");
        	else
        	{
			*directory = malloc (PATH_MAX);
			*directory = getcwd(*directory, PATH_MAX);
		}
	}
}
void showProcs(process** proc)
{
	printProcessList(proc);
}

int getNumOfPipes(cmdLine *tmp){
	int nCommands = 1;
	while (tmp->next != NULL){
		nCommands++;
		tmp = tmp->next;
	}
	return nCommands - 1;
}
void IOredirection(cmdLine *pCmdLine){
	int fdInput;
	int fdOutput;
	if (pCmdLine->inputRedirect != NULL){
		fdInput = open(pCmdLine->inputRedirect, O_RDONLY | O_CREAT, 0644);
		dup2(fdInput, 0);
	}
	if (pCmdLine->outputRedirect != NULL){
		fdOutput = open(pCmdLine->outputRedirect, O_WRONLY | O_CREAT, 0644);
		dup2(fdOutput, 1);
	}
}
void executeWithPipe(cmdLine *pCmdLine){
	cmdLine* tmp = pCmdLine;
	int nPipes;
	nPipes = getNumOfPipes(tmp);
	int ** pipesArray = createPipes(nPipes);
	int i = 0;
	int j = 0;
	int status;
	int pid;
	
	while (pCmdLine){
		pid = fork();
		if (pid == 0) {//child
			if (pCmdLine->next){//if not first command
				if (dup2(pipesArray[j][1], 1) < 0){
					perror("\nfirst dup2 failure\n");
					exit(EXIT_FAILURE);
				}
				close(pipesArray[j][1]);
			}
			if (j != 0){
				if(dup2(pipesArray[j-1][0], 0) < 0){
					perror("\nsecond dup2 failure\n");
					exit(EXIT_FAILURE);
				}
				close(pipesArray[j-1][0]);
			}
			for (i = 0; i < nPipes; i++){
				close(pipesArray[i][0]);
				close(pipesArray[i][1]);
			}
			IOredirection(pCmdLine);
			if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) < 0){
				perror(pCmdLine->arguments[0]);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0){//error
				perror("\nerror\n");
				exit(EXIT_FAILURE);
		}
		close(pipesArray[j][1]);
		if (j != 0)
			close(pipesArray[j-1][0]);
		pCmdLine = pCmdLine->next;
		j++;
	}
	for (i = 0; i < nPipes + 1; i++){
		wait(&status);	
	}
	releasePipes(pipesArray, nPipes);
}

void execute(cmdLine *pCmdLine)
{
	if (pCmdLine->next != NULL){
		executeWithPipe(pCmdLine);
	}
	else{
		if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) == -1)
		{
			perror("Error occurred");
			freeCmdLines(pCmdLine);
			_exit(1);
		}
	}
}

int main (int argc, char **argv)
{
	int debug = 0;
	if(argc > 1)
	{
		if (strcmp(argv[1], "-d") == 0)
		{
			debug = 1;
		}
	}
	process* processList = NULL;
	char* directory = malloc (PATH_MAX);
	char* command = malloc(2048);
	directory = getcwd(directory, PATH_MAX);
	while(1)
	{
		printf("%s", directory);
		printf("$ ");
		fgets(command, 2048, stdin);
		
		cmdLine *execCom = parseCmdLines(command);
		char * command2;
		command2 = execCom->arguments[0];
		if(strcmp (execCom->arguments[0], "cd") == 0)
		{
			cd(execCom, &directory);
			if(debug == 1)
				fprintf(stderr, "command: cd");
		}
		else if (strcmp (execCom->arguments[0], "showprocs") == 0)
		{
			showProcs(&processList);
			if(debug == 1)
				fprintf(stderr, "command: showprocs");
		}
		else
		{
			int pid = fork();
			int status;
			if (strcmp(command, "quit\n") == 0)
			{
				_exit(0);
			}
			if (pid)
			{
				if(debug == 1)
					fprintf(stderr, "PID: %d\n", pid);
				if (strcmp(command2, "nap") != 0 && strcmp(command2, "stop") != 0)
				{
					addProcess(&processList, execCom, pid);
				}
				if(execCom->blocking == 1 && strcmp (execCom->arguments[0], "nap") != 0)
				{
					waitpid(pid, &status, 0);
				}
			}
			else
			{
				IOredirection(execCom);
				if(debug == 1)
					fprintf(stderr, "command: %s\n",(char*) execCom->arguments[0]);
				if (strcmp (execCom->arguments[0], "nap") == 0)
				{
					nap(atoi(execCom->arguments[1]), atoi(execCom->arguments[2]));
					if (debug == 1)
						fprintf(stderr, "command: nap");
					break;
				}
				if (strcmp (execCom->arguments[0], "stop") == 0)
				{
					stop(atoi(execCom->arguments[1]));
					if (debug == 1)
						fprintf(stderr, "command: stop");
					break;
				}
				execute(execCom);
			}

		}
	}
	return 0;
}
