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
    if((pid[0]=fork()) && (pid[1]=fork()))
    {
        wait(NULL);
        wait(NULL);
        printf("Parent\n");
    }
    else if(pid[0] == 0){
        printf("C1\n");
    }
    else if(pid[1] == 0)
    {
        if((pid[2]=fork()) && (pid[3]=fork()))
        {
            wait(NULL);
            wait(NULL);
            printf("C2\n");
        }
        else if(pid[2] == 0)
        {
            printf("C3\n");
        }
        else if(pid[3] == 0)
        {
            printf("C4\n");
        }
    }


    return 0;
}