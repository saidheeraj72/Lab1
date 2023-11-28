// CS21B2019 Devarakonda SLR Siddesh
#include <stdio.h>
#include <unistd.h>     // header file for fork(), getpid(), getppid(), sleep(), etc.
#include <sys/types.h>  // header file for data types pid_t, ssize_t, time_t, useconds_t, size_t, clock_t, etc.
#include <sys/wait.h>   // header file for wait(), waitpid(), waitid(), etc.

int findMinOrMax(int *arr, char type, int n) // function to find minimum or maximum element of array
{
    int i, min = arr[0], max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    if (type == '<') {
        return min;
    } else {
        return max;
    }
}

int main() {
    pid_t pid;      // pid_t is a signed integer type which is capable of representing a process ID.
    int n;

    printf("Enter the number of elements : ");
    scanf("%d", &n);
    
    int arr[n];     // array of size n to store elements
    printf("Enter elements of array      : ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid = fork();   // fork() returns 0 to the child process and returns the process ID of the child process to the parent process. 
    if (pid < 0)    // returns -1 if fork() fails to create a child process.
    {
        printf("Error");
        return 1;
    } 
    else if (pid == 0)
    {
        printf("\n----------Child process----------\n");

        for(int i = 0; i < n; i++)
            arr[i] += 2;
        
        printf("\nElements of array            : ");
        for(int i = 0; i < n; i++) 
            printf("%d ", arr[i]);
        printf("\n");

        printf("Addresses of array elements  : ");
        for(int i = 0; i < n; i++)
            printf("%p ", &arr[i]);
        printf("\n");

        printf("Maximum element of array     : %d\n", findMinOrMax(arr, '>', n));
        printf("Process ID of child process  : %d\n", getpid());    // getpid() returns the process ID of the calling process.
        printf("Process ID of parent process : %d\n", getppid());   // getppid() returns the process ID of the parent of the calling process.
    } 
    else 
    {
        printf("\n----------Parent process----------\n");

        for(int i = 0; i < n; i++)
            arr[i] -= 3;

        printf("\nElements of array            : ");
        for(int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        printf("Addresses of array elements  : ");
        for(int i = 0; i < n; i++)
            printf("%p ", &arr[i]);
        printf("\n");

        printf("Minimum element of array     : %d\n", findMinOrMax(arr, '<', n));
        printf("Process ID                   : %d\n", getpid());    // getpid() returns the process ID of the calling process.
        printf("Process ID of parent process : %d\n", getppid());   // getppid() returns the process ID of the parent of the calling process.
        wait(NULL);     // wait() causes the parent process to wait for the child process to finish executing.
    }
    return 0;
}