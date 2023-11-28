// Roll: CS21B2019
// Name: Devarakonda SLR Siddesh
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 512

// Define a structure for the message
typedef struct {
    long int msg_type;  // Message type (used for message selection)
    int data[MAX];      // Data array to hold integers
} Msg;

int main() {
    int msgid;           // Message queue ID
    Msg msg;             // Message structure

    msg.msg_type = 1;   // Set the message type for receiving

    // Get the message queue with key 2019 and read permissions
    msgid = msgget((key_t)2019, 0644);
    if (msgid == -1) {
        printf("Error in creating message queue\n");
        exit(0);
    }

    // Receive a message from the message queue
    if(msgrcv(msgid, (void *)&msg, MAX * sizeof(int), msg.msg_type, 0) == -1)
    {
        printf("Not able to receive message\n");
        exit(0);
    }

    int odd = 0; // Counter for odd numbers
    printf("Odd numbers are : ");
    int n = msg.data[0]; // Get the count of numbers from the message
    for (int i = 1; i <= n; i++) {
        if (msg.data[i] % 2 == 1) { // Check if the number is odd
            printf("%d ", msg.data[i]); // Print odd number
            odd++; // Increment the odd count
        }
    }
    
    // Print the number of odd numbers found
    printf("\nNumber of odd Numbers : %d\n", odd);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, 0);

    return 0;
}