// Round Robin Algorithm for Preemptive Scheduling

//  Write a C program to implement round-robin scheduling.
// (i)Take input from the user as P_id, arrival time, burst Time, and time quantum.
// (ii) Show the turnaround time, waiting time, and response time for each task.
// (iii) Compute average turnaround time, waiting time, and response time.
// (iv) Count the number of context switches (excluding the count at the beginning of the first execution process and the end of the last execution process)
// (v) Your algorithm should work for both the scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time
// Note: You can use only integers for process id. Use the array implementation(dynamically using malloc) for the Queue. At the end of the program remove the queue from the memory.

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int front = -1;
int rear = -1;

struct process
{
    int pid, at, bt;
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
}

void dequeue(struct process *q, struct process *p, int pos)
{
    if(front == -1 || front > rear)
    {
        printf("Queue is empty\n");
        return;
    }
    if(pos != -1)
    {
        q[front].tat = q[front].ft - q[front].at;
        q[front].wt = q[front].tat - q[front].bt;
        p[pos] = q[front];
    }
    front++;
}

int createReadyQueue(struct process *readyQueue, struct process *p, int n, int t)
{
    int curr_time = 0;
    int completed = 0;
    int task_left = 0;
    int context_switch = 0;
    struct process temp;
    
    while(completed != n)
    {
        for(int i = 0; i < n; i++)
        {
            if(!p[i].started && p[i].at <= curr_time)
            {
                enqueue(readyQueue, p[i]);
                p[i].started = 1;
            }
        }
        if(task_left)
        {
            enqueue(readyQueue, temp);
            task_left = 0;
        }
        if(front > rear || front == -1)
        {
            curr_time++;
            continue;
        }
        if(readyQueue[front].bt - readyQueue[front].run_time > t)
        {
            if(readyQueue[front].run_time == 0)
                readyQueue[front].rt = curr_time - readyQueue[front].at;
            curr_time += t;
            readyQueue[front].run_time += t;
            task_left = 1;
            temp = readyQueue[front];
            printf("%d\n", temp.pid);
            dequeue(readyQueue, p, -1);
            context_switch++;
        }
        else
        {
            if(readyQueue[front].run_time == 0)
                readyQueue[front].rt = curr_time - readyQueue[front].at;
            curr_time += readyQueue[front].bt - readyQueue[front].run_time;
            readyQueue[front].run_time = readyQueue[front].bt;
            readyQueue[front].ft = curr_time;
            int pos = findIndex(readyQueue[front].pid, p, n);
            printf("%d\n", readyQueue[front].pid);
            dequeue(readyQueue, p, pos);
            completed++;
            context_switch++;
        }
    }

    return context_switch - 1;
}

int main()
{
    int n, pid = 1, t_q;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &t_q);

    struct process *p = (struct process *)malloc(n * sizeof(struct process));

    for(int i = 0; i < n; i++)
    {
        int at, bt;
        p[i].pid = pid;
        printf("For Process-%d : \n", pid++);

        printf("\tEnter Arrival-Time (AT) : ");
        scanf("%d", &p[i].at);

        printf("\tEnter Burst-Time (BT)   : ");
        scanf("%d", &p[i].bt);

        p[i].started = 0;
        p[i].run_time = 0;
    }

    struct process *readyQueue = (struct process *)malloc(MAX * sizeof(struct process));

    int c_s = createReadyQueue(readyQueue, p, n, t_q);

    int totTAT = 0, totWT = 0, totRT = 0;

    printf("\nPID\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ft, p[i].tat, p[i].wt, p[i].rt);
        totTAT += p[i].tat;
        totWT += p[i].wt;
        totRT += p[i].rt;
    }
    printf("\nAverage Turn-Around Time (TAT) : %0.3f\n", (float)totTAT / n);
    printf("Average Waiting Time (WT)      : %0.3f\n", (float)totWT / n);
    printf("Average Response Time (RT)     : %0.3f\n", (float)totRT / n);
    printf("Number of Context Switches     : %d\n", c_s);

    return 0;
}