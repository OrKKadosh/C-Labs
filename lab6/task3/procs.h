//
// Created by Dan K on 16/05/2022.
//

#ifndef LAB5_PROCS_H
#define LAB5_PROCS_H

#endif //LAB5_PROCS_H
#define TERMINATED -1
#define RUNNING 1
#define SUSPENDED 0

typedef struct process
{
    cmdLine* cmd; /* the parsed command line*/
    pid_t pid; /* the process id that is
running the command*/
    int status; /* status of the process:
RUNNING/SUSPENDED/TERMINATED */
    struct process *next; /* next process in chain */
} process;
void addProcess(process** process_list, cmdLine* cmd, pid_t pid);
void printProcessList(process** process_list);
void freeProcessList(process* process_list);
void updateProcessList(process **process_list);
void updateProcessStatus(process* process_list, int pid, int status);
char* statusToString(int status);