#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include "LineParser.h"
#include "procs.h"
char* statusToString(int status)
{
	if (status == 1)
	{
		return "Running";
	}
	if (status == 0)
	{
		return "Suspended";
    	}
	if (status == -1)
	{
		return "Terminated";
	}
	return "";
}

void addProcess(process** process_list, cmdLine* cmd, pid_t pid)
{
	process* newProc = malloc(sizeof (process));
	newProc->cmd = cmd;
	newProc->pid = pid;
	newProc->status = RUNNING;
	newProc->next = NULL;

	if(*process_list == NULL)
		*process_list = newProc;
	else
	{
		process* currProc = *process_list;
		while(currProc->next != NULL)
		{
			currProc = currProc->next;
		}
		currProc->next = newProc;
	}
}
void printProcessList(process** process_list)
{
    process * curr = *process_list;
    if(*process_list == NULL)
        printf("Noting to print\n");
    else
    {
        updateProcessList(process_list);
	printf("PID\t\tCOMMAND\t\tSTATUS\n");
        while (curr->next != NULL)
        {
            
            
		printf("%d\t\t%s\t\t%s\n", curr->pid, curr->cmd->arguments[0], statusToString(curr->status));
            curr = curr->next;
        }
        printf("%d\t\t%s\t\t%s\n", curr->pid, curr->cmd->arguments[0], statusToString(curr->status));
    }
}

void freeProcessList(process* process_list)
{
	process *curr;

	while (process_list != NULL)
	{
		curr = process_list;
		process_list = process_list->next;
		freeCmdLines(curr->cmd);
		free(curr);
	}
}
void updateProcessList(process **process_list)
{
	process * curr = *process_list;
	while (curr != NULL)
	{
		int status;
		int wait_status = RUNNING;
		int wait = waitpid(curr->pid, &status, WNOHANG | WUNTRACED | WCONTINUED);


		if(wait != 0)
		{
			if (WIFEXITED(status) || WIFSIGNALED(status))
				wait_status = TERMINATED;
			if (WIFSTOPPED(status))
				wait_status = SUSPENDED;
			if (WIFCONTINUED(status))
				wait_status = RUNNING;
			updateProcessStatus(curr, curr->pid, wait_status);
		}
		curr = curr->next;
	}
}
void updateProcessStatus(process* process_list, int pid, int status)
{
	process* curr = process_list;
	while (curr->pid != pid)
	{
		curr = curr->next;
	}
	curr->status = status;
}
