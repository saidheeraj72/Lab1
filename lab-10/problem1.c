// CS21B2019
// Devarakonda SLR Siddesh
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define SIZE 100

void sigfpe_handler(int signum)
{
    printf("Division by zero error!!\n");
}

void sigusr1_handle(int signum)
{
    printf("---------- Fork Failed ----------\n");
}

int main()
{
    pid_t pid;
    pid = fork();
    signal(SIGFPE, sigfpe_handler);

    if(pid > 0)
    {
        wait(NULL);
        printf("--------- Parent Process ---------\n");
        int arr[8] = {2, 1, 3, 0, 5, 0, 7, 9};
        int n;
        printf("Enter a number: ");
        scanf("%d", &n);
        for(int i = 0; i < sizeof(arr)/sizeof(int); i++)
        {
            if(arr[i] == 0)
            {
                printf("%d %% %d = ", n, arr[i]);
                raise(SIGFPE);
            }
            else
            {
                int rem = n % arr[i];
                printf("%d %% %d = %d\n", n, arr[i], rem);
            }
        }
    }
    else if(pid == 0)
    {
        printf("---------- Child Process ----------\n");
        int num = 11;
        srand(time(NULL));
        printf("Random numbers between 10 and 30\n");
        while(num <= 20)
        {
            num = rand() % 21 + 10;
            printf("%d\n", num);
        }
        printf("Child process terminated\n");
        exit(0);
    }
    else
    {
        signal(SIGUSR1, sigusr1_handle);
        raise(SIGUSR1);
    }

    return 0;
}