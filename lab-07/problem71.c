// CS21B2019 DEVARAKONDA SLR SIDDESH

// Write a program using pipe() and fork() in which parent process takes one string as input.
// The same is sent to the child using pipe1 and child will reverse it. 
// After the reversing is completed, the child process will send it (reversed string) to parent process using pipe2. 
// Subsequently, parent process will read the string and displays it.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 100

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    int p1, p2;

    p1 = pipe(pipe1);
    p2 = pipe(pipe2);

    if(p1 < 0 || p2 < 0)
        printf("Pipe Failed");

    pid = fork();
    if(pid > 0)
    {
        printf("---Parent Process my id is %d and my parent id is %d---\n", getpid(), getppid());

        char string[MAX], reversed[MAX];
        printf("Enter a string : ");
        scanf("%s", string);

        close(pipe1[0]);
        write(pipe1[1], string, sizeof(string));

        close(pipe2[1]);
        read(pipe2[0], reversed, sizeof(reversed));

        wait(NULL);
        printf("---Parent Process my id is %d and my parent id is %d---\n", getpid(), getppid());
        printf("Reversed string: %s\n", reversed);
    }
    else if(pid == 0)
    {
        char string[MAX], reversed[MAX];

        close(pipe1[1]);
        read(pipe1[0], string, sizeof(string));
        printf("\n---Child Process my id is %d and my parent id is %d---\n", getpid(), getppid());
        printf("Received string from parent process : %s\n", string);

        int i = strlen(string) - 1, j = 0;
        while(i >= 0)
            reversed[j++] = string[i--];

        close(pipe2[0]);
        write(pipe2[1], reversed, sizeof(reversed));

        printf("Reversed the string and sent to parent process\n\n");
    }
    else
        printf("Fork function call Failed");

    return 0;
}