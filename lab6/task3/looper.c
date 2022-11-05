#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include "LineParser.h"

void handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("caught Ctrl+C signal\n");
    }
    if (signum == SIGTSTP)
    {
        printf("caught stop signal\n");
    }
    if (signum == SIGCONT)
    {
        printf("caught cont signal\n");
    }
    signal(signum, SIG_DFL);
    raise(signum);
    if (signum == SIGCONT){
        signal(SIGTSTP, handler);
    }
    if (signum == SIGTSTP){
        signal(SIGCONT, handler);
    }

}

int main(int argc, char **argv)
{

	printf("Starting the program\n");
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGCONT, handler);
	while(1) {
		sleep(2);
	}

	return 0;
}