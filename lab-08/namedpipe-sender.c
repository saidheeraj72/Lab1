// Roll: CS21B2019
// Name: Devarakonda SLR Siddesh

// Write two different programs (Sender and Receiver) in C to demonstrate IPC using FIFO Named Pipe. 
// Process "Sender.c" will write one integer value (Say A) as a message in FIFO. "Receiver.c" will read that message. 
// After reading the message, it will find the one’s complement of A and name it as B1. 
// Then, it will write B on to the pipe. "Sender.c" will read the integer value B1 from the pipe and display it.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int fd1; // File descriptor for the FIFO
    char *myfifo = "/tmp/myfile1.txt"; // Path to the named pipe (FIFO)

    // Create a named pipe with read and write permissions
    if (mkfifo(myfifo, 0666) == -1) {
        printf("Error in creating named pipe\n");
        return 1;
    }

    int a;
    printf("Enter a number : ");
    scanf("%d", &a);

    // Open the named pipe for writing
    printf("[Sent] Sending %d into fifo file\n", a);
    fd1 = open(myfifo, O_WRONLY);

    // Write the value of 'a' into the named pipe
    write(fd1, &a, sizeof(a));
    close(fd1);

    int b;

    // Open the named pipe for reading
    fd1 = open(myfifo, O_RDONLY);
    // Read the 1's complement of 'a' from the named pipe
    read(fd1, &b, sizeof(b));

    // Print the received value
    printf("[Received] The 1's complement of %d : %d\n", a, b);

    // Close the file descriptor and remove the named pipe
    close(fd1);
    unlink(myfifo);

    return 0;
}
