// Roll: CS21B2019
// Name: Devarakonda SLR Siddesh

// Write two different programs (Sender and Receiver) in C to demonstrate IPC using message queue. 
// Process "Sender.c" will take input of atleast 10 numbers and share these numbers with the "Receiver.c" process 
// using message queue. The "Receiver.c" will check each numbers and displays 
// how many odd numbers are there among those numbers and displays them.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 512

// Define a structure for the message
typedef struct {
    long int msg_type; // Message type (used for message selection)
    int data[MAX];    // Data array to hold integers
} Msg;

int main() {
    int msgid, n; // Message queue ID and number of integers to send
    Msg msg;      // Message structure
    int buffer[MAX]; // Buffer to store user input integers

    // Create or get the message queue with key 2019 and permissions
    msgid = msgget((key_t) 2019, 0666 | IPC_CREAT);
    if (msgid == -1) {
        printf("Error in creating message queue\n");
        exit(0);
    }

    printf("Enter No. of numbers : ");
    scanf("%d", &n);

    printf("Enter the numbers : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &buffer[i]);

    // Prepare the message
    msg.msg_type = 1;   // Set the message type
    msg.data[0] = n;    // Store the count of numbers in the data array
    for (int i = 1; i <= n; i++)
        msg.data[i] = buffer[i - 1]; // Store the numbers in the data array

    // Send the message to the message queue
    int msgsnd_status = msgsnd(msgid, (void *)&msg, MAX * sizeof(int), 0);
    if (msgsnd_status == -1)
        printf("Message not sent\n");
    else
        printf("Message sent successfully\n");

    return 0;
}