// Roll: CS21B2019
// Name: Devarakonda SLR Siddesh
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int ones_comp(int a)
{
    int b = 0, p = 1;
    while(a > 0)
    {
        int m = a % 2;
        if(m == 0)
            b = b + p;
        p = p * 2;
        a = a / 2;
    }
    return b;
}

int main() 
{
    int fd1;                    // File descriptor for the FIFO (named pipe)
    char *myfifo = "/tmp/myfile1.txt"; // Path to the FIFO
    int a;                      // Variable to store the received number

    // Open the FIFO for reading
    fd1 = open(myfifo, O_RDONLY);
    
    // Read an integer from the FIFO
    read(fd1, &a, sizeof(a));
    
    // Close the FIFO after reading
    close(fd1);

    // Print the received number
    printf("[Received] Read %d from fifo file\n", a);
    printf("Received number: %d\n", a);

    // Calculate the 1's complement of the received number
    int b = ones_comp(a);

    // Open the FIFO for writing
    fd1 = open(myfifo, O_WRONLY);
    
    // Write the 1's complement back to the FIFO
    write(fd1, &b, sizeof(b));
    
    // Close the FIFO after writing
    close(fd1);

    // Print a message indicating the 1's complement was sent
    printf("[Sent] Written 1's complement of %d\n", a);

    return 0;
}