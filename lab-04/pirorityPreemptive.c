// CS21B2019 DEVARAKONDA SLR SIDDESH

// Priority Algorithm for Preemptive Scheduling
// 1. Implement a preemptive priority scheduling approach.
// (i) Provide the input as P_id, arrival time (all are arriving at a different time), priority of each process, and burst time.
// (ii) Show the Completion time, turnaround time, waiting time, and response time for each process.
// (iii) Compute average turnaround time, waiting time, and response time.
// (iv) Print the schedule for the given input.
// Note: You can use only integers for process id. Use the array implementation (dynamically using malloc()) for the Queue. At the end of the program remove the queue from the memory.

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int front = -1;
int rear = -1;

struct process
{
    int pid, priority, at, bt;
    int ft, tat, wt, rt;
    int started;
    int run_time;
};

int findIndex(int pid, struct process *p, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(p[i].pid == pid)
        {
            return i;
        }
    }
    return -1;
}

void sortQueue(struct process *q)
{
    for(int i = front; i < rear; i++)
    {
        for(int j = front; j < rear; j++)
        {
            if(q[j].priority > q[j + 1].priority)
            {
                struct process temp = q[j];
                q[j] = q[j + 1];
                q[j + 1] = temp;
            }
        }
    }
}

void enqueue(struct process *q, struct process p)
{
    if(rear == MAX - 1)
    {
        printf("Queue is full\n");
        return;
    }
    if(front == -1)
        front = 0;
    rear++;
    q[rear] = p;
    sortQueue(q);
}

void dequeue(struct process *q, struct process *p, int pos)
{
    if(front == -1 || front > rear)
    {
        printf("Queue is empty\n");
        return;
    }
    q[front].tat = q[front].ft - q[front].at;
    q[front].wt = q[front].tat - q[front].bt;
    p[pos] = q[front];
    front++;
}

void createReadyQueue(struct process *readyQueue, struct process *p, int n)
{
    int curr_time = 0;
    int completed = 0;
    
    while(completed != n)
    {
        for(int i = 0; i < n; i++)
        {
            if(!p[i].started && p[i].at == curr_time)
            {
                enqueue(readyQueue, p[i]);
                p[i].started = 1;
            }
        }
        if(front <=rear && front != -1) // if queue is not empty
        {
            if(readyQueue[front].run_time == readyQueue[front].bt) // if process is completed
            {
                readyQueue[front].ft = curr_time;
                int pos = findIndex(readyQueue[front].pid, p, n);
                dequeue(readyQueue, p, pos);
                completed++;
            }
            else
            {
                if(readyQueue[front].run_time == 0) // if process is starting
                    readyQueue[front].rt = curr_time - readyQueue[front].at;
                readyQueue[front].run_time++;
                curr_time++;
            }
        }
        else
        {
            curr_time++;
        }
    }
}

int main()
{
    int n, pid = 1;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process *p = (struct process *)malloc(n * sizeof(struct process));

    for(int i = 0; i < n; i++)
    {
        int at, bt, priority;
        p[i].pid = pid;
        printf("For Process-%d : \n", pid++);

        printf("\tEnter Arrival-Time (AT) : ");
        scanf("%d", &p[i].at);

        printf("\tEnter Burst-Time (BT)   : ");
        scanf("%d", &p[i].bt);
        
        printf("\tEnter Priority          : ");
        scanf("%d", &p[i].priority);

        p[i].started = 0;
        p[i].run_time = 0;
    }

    struct process *readyQueue = (struct process *)malloc(MAX * sizeof(struct process));

    createReadyQueue(readyQueue, p, n);

    int totTAT = 0, totWT = 0, totRT = 0;
    printf("\nPID\tPri\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].priority, p[i].at, p[i].bt, p[i].ft, p[i].tat, p[i].wt, p[i].rt);
        totTAT += p[i].tat;
        totWT += p[i].wt;
        totRT += p[i].rt;
    }
    printf("\nAverage Turn-Around Time (TAT) : %0.3f\n", (float)totTAT / n);
    printf("Average Waiting Time (WT)      : %0.3f\n", (float)totWT / n);
    printf("Average Response Time (RT)     : %0.3f\n", (float)totRT / n);

    return 0;
}