// CS21B2019 DEVARAKONDA SLR SIDDESH

// Write two programs (Given Program31.c and Program32.c).
// For Program31.c:
// In Parent Process:
// (a) Print your name, roll number, and Institution name 
// (b) Print process id and its parent process id and returned value of fork() system call.
// In Child Process,
// (a) Print id of the process, it’s parent process id, and returned value of fork() system call.
// (b) Use exec() system call to execute new program written in Program32.c. In Program32.c, write or compute anything of your choice. The executable file for Program32.c is (progam32).
// (c) Write a few printf statements after operation (b).
// Analyze the entire creation of the parent and child processes. Make sure that the parent process terminates after the child process has finished its execution.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        printf("Fork Failed\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("\n----------Child Process----------\n");
        printf("Child Process ID       : %d\n", getpid());
        printf("Parent Process ID      : %d\n", getppid());
        printf("Return value of fork() : %d\n", pid);
        execlp("./Program32", "Program32", NULL);
        printf("After execlp()\n");
    }
    else
    {
        printf("\n----------Parent Process----------\n");
        printf("Name: Siddesh Devarakonda\n");
        printf("Roll No: CS21B2019\n");
        printf("Institute: IIITDM Kancheepuram\n");
        printf("Process ID             : %d\n", getpid());
        printf("Parent Process ID      : %d\n", getppid());
        printf("Return value of fork() : %d\n", pid);
        wait(NULL);
        printf("After wait()\n");
    }

    return 0;
}