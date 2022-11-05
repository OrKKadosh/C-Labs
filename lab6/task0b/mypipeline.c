#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main(int argc, char** argv){
	int pid1;
	int pid2;
	char buf;
	int p[2];
	pipe(p);
	char* argvLS[3] = {"ls", "-l", 0};
	char* argvTail[4] = {"tail", "-n", "2", 0};
	int debug = 0;
	if(argc > 1)
	{
		if (strcmp(argv[1], "-d") == 0)
		{
			debug = 1;
		}
	}
	if (debug){
		fprintf(stderr, "(parent process>forking...)\n");
	}
	pid1 = fork();
	if (pid1 > 0) {
		if (debug){
			fprintf(stderr, "(parent process>created process with id: %d)\n", pid1);
			fprintf(stderr, "(parent process>closing the write end of the pipe...)\n");
		}
		close(p[1]);
		pid2 = fork();
		if (pid2 > 0){
			if (debug){
				fprintf(stderr, "(parent_process>closing the read end of the pipe...)\n");
			}
			close(p[0]);
			if (debug){
				fprintf(stderr, "(parent process>waiting for child2 process to terminate...)\n");
			}
			wait(NULL);
			
		}
		else{//child2 - tail
			if (debug){
				fprintf(stderr, "(child2 process>redirecting stdin to the read end of the pipe...)\n");
				fprintf(stderr, "(child2 process>going to execute cmd: tail -n 2...\n");
			}
			close(0);
			int fdRead_dup = dup(p[0]);
			close(p[0]);
			execvp(argvTail[0], argvTail);
			
		}
		if (debug){
			fprintf(stderr, "(parent process>waiting for child1 process to terminate...)\n");
		}
		wait(NULL);
		if (debug){
			fprintf(stderr, "(parent process>exiting...)\n");
		}
	}
	else {//child1 - ls
		if (debug){
			fprintf(stderr, "(child1 process>redirecting stdout to the write end of the pipe...)\n");
			fprintf(stderr, "(child1 process>going to execute cmd: ls -l...\n");
		}
		close(1);
		int fdWrite_dup = dup(p[1]);
		close(p[1]);
		execvp(argvLS[0], argvLS);
	}
	return 0;
}
