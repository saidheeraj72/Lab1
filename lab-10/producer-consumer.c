// CS21B2019
// DEVARAKONDA SLR SIDDESH
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define SIZE 5
int buffer[SIZE];
int count = 0;

sem_t mutex, empty, full;

int produce_item()
{
    sleep(rand() % 2 + 1);
    return rand() % 100;
}

void consume_item(int item)
{
    sleep(rand() % 2 + 1);
    printf("Consumed item: %d\n", item);
}

void *producer()
{
    int item;
    for(int i = 0; i < 2*SIZE; i++)
    {
        item = produce_item();

        sem_wait(&empty);

        sem_wait(&mutex);
        buffer[count++] = item;
        printf("Produced item: %d\n", item);
        sem_post(&mutex);

        sem_post(&full);
    }
}

void *consumer()
{
    int item;
    for(int i = 0; i < 2*SIZE; i++)
    {
        sem_wait(&full);

        sem_wait(&mutex);
        item = buffer[0];
        for(int j = 0; j < count - 1; j++)
            buffer[j] = buffer[j+1];
        count--;
        sem_post(&mutex);

        sem_post(&empty);

        consume_item(item);
    }
}

int main()
{
    srand(time(NULL));
    
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    pthread_t producer_pid, consumer_pid;

    if(pthread_create(&producer_pid, NULL, producer, NULL) != 0)
    {
        perror("Not abel to create producer thread");
        exit(1);
    }

    if(pthread_create(&consumer_pid, NULL, consumer, NULL) != 0)
    {
        perror("Not abel to create consumer thread");
        exit(1);
    }
    
    pthread_join(producer_pid, NULL);
    pthread_join(consumer_pid, NULL);

    return 0;
}