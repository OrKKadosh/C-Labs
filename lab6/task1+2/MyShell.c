
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
void executeWithPipe(cmdLine *pCmdLine){
	int pid1;
	int pid2;
	char buf;
	int p[2];
	pipe(p);
	pid1 = fork();
	if (pid1 > 0) {
		close(p[1]);
		pid2 = fork();
		if (pid2 > 0){
			close(p[0]);
			wait(NULL);	
		}
		else{//child2
			close(0);
			int fdRead_dup = dup(p[0]);
			close(p[0]);
			if (execvp(pCmdLine->next->arguments[0], pCmdLine->next->arguments) == -1){
				perror("Error occurred");
				freeCmdLines(pCmdLine);
				_exit(1);
			}	
		}
		wait(NULL);
	}
	else {//child1
		close(1);
		int fdWrite_dup = dup(p[1]);
		close(p[1]);
		if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) == -1){
			perror("Error occurred");
			freeCmdLines(pCmdLine);
			_exit(1);
		}
	}
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
    	int fdInput;
	int fdOutput;
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
				if (execCom->inputRedirect != NULL){
					fdInput = open(execCom->inputRedirect, O_RDONLY | O_CREAT, 0644);
					dup2(fdInput, 0);
				}
				if (execCom->outputRedirect != NULL){
					fdOutput = open(execCom->outputRedirect, O_WRONLY | O_CREAT, 0644);
					dup2(fdOutput, 1);
				}
				

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
