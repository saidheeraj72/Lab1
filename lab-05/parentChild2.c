// CS21B2019 DEVARAKONDA SLR SIDDESH

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sortArray(int *arr, int n) // function to sort array
{
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < (n - i - 1); j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        } 
    }
}

void printArray(int *arr, int n)    // function to print array
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    pid_t pid;      // pid_t is a signed integer type which is capable of representing a process ID.
    int n;

    pid = fork();   //fork() returns 0 to the child process and returns the process ID of the child process to the parent process.
    if(pid < 0)
        printf("Error");
    else if(pid == 0)
    {
        printf("\n----------Child process----------\n");

        int n;
        printf("Enter the number of elements : ");
        scanf("%d", &n);

        int *arr = (int *)malloc(n * sizeof(int));    // array of size n to store elements
        printf("Enter elements of array      : ");
        for(int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        
        printf("\nElements of array            : ");
        printArray(arr, n);

        printf("Addresses of array elements  : ");
        for(int i = 0; i < n; i++)
            printf("%p ", &arr[i]);
        printf("\n");

        sortArray(arr, n);

    printf("\nElements of sorted array     : ");
    printArray(arr, n);
    }
    else
    {
        wait(NULL);
        printf("\n----------Parent process----------\n");

        int n;
        printf("Enter the number of elements : ");
        scanf("%d", &n);
        
        int *arr = (int *)malloc(n * sizeof(int));    // array of size n to store elements
        printf("Enter elements of array      : ");
        for(int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        
        printf("\nElements of array            : ");
        printArray(arr, n);

        printf("Addresses of array elements  : ");
        for(int i = 0; i < n; i++)
            printf("%p ", &arr[i]);
        printf("\n");

        sortArray(arr, n);

        printf("\nElements of sorted array     : ");
        printArray(arr, n);
    }

    return 0;
}