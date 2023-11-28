// CS21B2019
// DEVARAKONDA SLR SIDDESH
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

sem_t mutex;
sem_t forks[N];

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

void thinking(int i)
{
    printf("Philosopher-%d is thinking...\n", i + 1);
    sleep(1);
}

void eating(int i)
{
    printf("Philosopher-%d is eating...\n", i + 1);
    sleep(1);
}

int left(int i)
{
    return (i + N - 1) % N;
}

int right(int i)
{
    return (i + 1) % N;
}

int check_available(int i)
{
    if(state[i] == HUNGRY && state[left(i)] != EATING && state[right(i)] != EATING)
    {
        state[i] = EATING;
        return 1;
    }
    return 0;
}

void *philosopher(void *arg)
{
    int *i = arg;
    while(1)
    {
        sem_wait(&mutex);
            state[*i] = HUNGRY;
            sleep(1);
            int if_eat = check_available(*i);
        if(if_eat)
        {
            printf("Philosopher-%d is hungry...\n", *i + 1);
            sem_wait(&forks[left(*i)]);
            sem_wait(&forks[*i]);
            printf("\t - Philosopher-%d 'took-forks' %d and %d\n", *i + 1, left(*i) + 1, *i + 1);
            eating(*i);
            sem_post(&mutex);
            sem_wait(&mutex);
                state[*i] = THINKING;
                sem_post(&forks[left(*i)]);
                sem_post(&forks[*i]);
                printf("\t - Philosopher-%d 'put-forks' %d and %d\n", *i + 1, left(*i) + 1, *i + 1);
                thinking(*i);
            sem_post(&mutex);
        }
        else
        {
            state[*i] = THINKING;
        }
    }
}

int main()
{
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);
    for(int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    
    for(int i = 0; i < N; i++)
    {
        thinking(i);
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}