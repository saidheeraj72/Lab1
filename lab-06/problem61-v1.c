// CS21B2019 DEVARAKONDA SLR SIDDESH

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int num = 1;

int main()
{
    pid_t pid[4];
    pid[0] = fork();
    if(pid[0] == 0)
        printf("CHild 1 my id is %d and my parent id is %d\n", getpid(), getppid());
    else if(pid[0] > 0)
    {
        pid[1] = fork();
        if(pid[1] == 0)
        {
            pid[2] = fork();
            if(pid[2] == 0)
                printf("Child 3 my id is %d and my parent id is %d\n", getpid(), getppid());
            else if(pid[2] > 0)
            {
                pid[3] = fork();
                if(pid[3] == 0)
                    printf("Child 4 my id is %d and my parent id is %d\n", getpid(), getppid());
                else if(pid[3] > 0)
                {
                    wait(NULL);
                    wait(NULL);
                    printf("Child 2 my id is %d and my parent id is %d\n", getpid(), getppid());
                }
                else
                {
                    printf("Error in creating child process");
                }
            }
            else
            {
                printf("Error in creating child process");
            }
        }
        else if(pid[1] > 0)
        {
            wait(NULL);
            wait(NULL);
            printf("Parent Process my id is %d and my parent id is %d\n", getpid(), getppid());
        }
        else
        {
            printf("Error in creating child process");
        }
    }
    else
    {
        printf("Error in creating child process");
    }

    return 0;
}