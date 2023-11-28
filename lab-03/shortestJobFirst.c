// CS21B2019 DEVARAKONDA SLR SIDDESH

// 1. Write a C program to implement the Shortest Job First Scheduling Algorithm.
// (i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply SJF.
// (ii) Your algorithm should work for both scenarios: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.
// (iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.
// (iv) Further compute the average waiting time and average turnaround time.
// (v) Print the schedule for the given input.
// Note: You can use only integers for process id. Use the min heap data structure (using linked list) to implement SJF Queue.

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int pid, at, bt;
    int ft, tat, wt, rt;
    int started;
    struct Node *next;
};

struct Node *head = NULL;
float totWT = 0, totTAT = 0;

void swapNodes(struct Node *a, struct Node *b){
    int temp0 = a->bt;
    a->bt = b->bt;
    b->bt = temp0;
    int temp1 = a->pid;
    a->pid = b->pid;
    b->pid = temp1;
    int temp2 = a->at;
    a->at = b->at;
    b->at = temp2;
}

void heapify(struct Node* node){
    struct Node *min = node;
    struct Node *l = node->next;
    struct Node *r = l ? l->next : NULL;
    if(l && l->bt < min->bt)
    {
        min = l;
    }
    if(r && r->bt < min->bt)
    {
        min = r;
    }
    if(min != node)
    {
        swapNodes(min, node);
        heapify(min);
    }
}

void popProcess(struct Node *disk, int pid, int n)
{
    struct Node *process = head;
    for(int i = 0; i < n; i++)
    {
        if(disk[i].pid == pid)
        {
            disk[i].ft = process->ft;
            disk[i].tat = process->tat;
            disk[i].wt = process->wt;
            disk[i].rt = process->rt;
            break;
        }
    }
    head = head->next;
    free(process);
}

void executeProcesses(struct Node *disk, int n)
{
    int finishTime = 0;
    int completedTasks = 0;
    while(completedTasks < n)
    {
        for(int i = 0; i < n; i++)
        {
            if(!disk[i].started && disk[i].at <= finishTime)
            {
                struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
                disk[i].started = 1;
                temp->pid = disk[i].pid;
                temp->at = disk[i].at;
                temp->bt = disk[i].bt;
                temp->started = 1;
                temp->next = head;
                head = temp;
                struct Node *ptr = head;
                while(ptr != NULL)
                {
                    heapify(ptr);
                    ptr=ptr->next;
                }
            }
        }
        finishTime += head->bt;
        head->ft = finishTime;
        head->tat = head->ft - head->at;
        head->wt = head->tat - head->bt;
        head->rt = head->tat - head->bt;
        totWT += head->wt;
        totTAT += head->tat;
        popProcess(disk, head->pid, n);
        completedTasks++;
    }
}

void printDisk(struct Node *disk, int n)
{
    printf("\nPID\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", disk[i].pid, disk[i].at, disk[i].bt, disk[i].ft, disk[i].tat, disk[i].wt, disk[i].rt);
    }
}

int main()
{
    int n, pid = 1;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    struct Node disk[n];
    
    for(int i = 0 ; i < n ; i++)
    {
        int at, bt;
        printf("For Process-%d : \n", pid);
        printf("\tEnter Arrival-Time (AT) : ");
        scanf("%d", &at);
        printf("\tEnter Burst-Time (bt)   : ");
        scanf("%d", &bt);
        disk[i].pid = pid++;
        disk[i].at = at;
        disk[i].bt = bt;
        disk[i].started = 0;
        disk[i].next = NULL;
    }
    executeProcesses(disk, n);
    printDisk(disk, n);
    printf("\nAverage Waiting time (WT)    : %0.3f\n",totWT/n);
    printf("Average Turn Around Time (TAT) : %0.3f\n",totTAT/n);
    
    
    return 0;
}