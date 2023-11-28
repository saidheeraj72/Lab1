//CS21B2019 DSLR SIDDESH

// Write a C program to implement First Come First Serve CPU Scheduling Algorithm.
// (i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply FCFS.
// (ii) Your algorithm should work for both scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.
// (iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.
// (iv) Further compute the average waiting time and average turnaround time.
// (v) Print the schedule for the given input.
// Note: You can use only integers for process id. Use the linked list implementation for the Queue.

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int pid;
    int at;
    int bt;
    int ft;
    int tat;
    int wt;
    int rt;
    struct node *next;
};

struct node *front = NULL;
struct node *rear = NULL;
int pid = 1;

void enqueue(int pid, int at, int bt)
{
    struct node *p;
    
    p = (struct node *)malloc(sizeof(struct node));
    
    p->pid = pid;
    p->at = at;
    p->bt = bt;
    p->next=NULL;
    
    if(front==NULL && rear==NULL)
    {
        front = rear = p;
    }
    else
    {
        rear->next = p;
        rear = p;
    }
}

void dequeue()
{
    struct node *temp;
    if(front == NULL && rear == NULL)
        printf("Queue is empty\n");
    else
    {
        temp = front;
        printf("P_id | AT | BT | FT | TAT | WT | RT\n");
        printf(" %d   | %d  | %d  | %d  |  %d  | %d  | %d\n", temp->pid, temp->at, temp->bt, temp->ft, temp->tat, temp->wt, temp->rt);
        front = front->next;
        free(temp);
    }
}

void display()
{
    struct node *temp;
    if(front == NULL && rear == NULL)
        printf("Queue is empty!!");
    else
    {
        temp=front;
        printf("\nP_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
        while(temp != NULL)
        {
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", temp->pid, temp->at, temp->bt, temp->ft, temp->tat, temp->wt, temp->rt);
            temp = temp->next;
        }
    }
}

void calculation(int n)
{
    struct node *temp = front;
    int prev_ft = temp->at;
    float totTAT = 0, totWT = 0;
    while(temp != NULL)
    {
        temp->ft = prev_ft + temp->bt;
        temp->tat = temp->ft - temp->at;
        temp->wt = temp->tat - temp->bt;
        temp->rt = temp->wt;
        prev_ft = temp->ft;
        totTAT += temp->tat;
        totWT += temp->wt;
        temp = temp->next;
    }
    
    display();
    printf("\nAverage Waiting Time     : %0.3f\n",totWT/n);
    printf("Average Turn Around Time : %0.3f\n",totTAT/n);
}

int main()
{
   int n, at, bt;
   printf("Enter the number of processes : ");
   scanf("%d", &n);
   
   for(int i = 0 ; i < n ; i++)
   {    printf("For Process-%d : \n", pid++);
        printf("\tEnter Arrival-Time (AT) : ");
        scanf("%d", &at);
        printf("\tEnter Burst-Time (BT)   : ");
        scanf("%d", &bt);
        enqueue(pid - 1, at, bt);
   }
   
   calculation(n);

    return 0;
}