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

sem_t mutex, wrt;
int read_count = 0;

void *writer()
{
    while(1)
    {
        sleep(rand() % 3);
        sem_wait(&wrt);
        printf("Writer is writing\n");
        sem_post(&wrt);
    }
}

void *reader(i)
{
    long int i = (long int)i;
    while(1)
    {
        sem_wait(mutex);
        read_count++;
        if(read_count == 1)
            sem_wait(wrt);
        sem_post(mutex);
        printf("Reader %d is reading\n", i + 1);
        sem_wait(mutex);
        read_count--;
        if(read_count == 0)
            sem_post(wrt);
        sem_post(mutex);
    }
}

int main()
{
    srand(time(NULL));
    
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, SIZE);

    pthread_t writer_pid, reader_pid[5];

    pthread_create(&writer_pid, NULL, writer, NULL);

    for(long int i = 0; i < 5; i++)
        pthread_create(&reader_pid[i], NULL, reader, i);
    
    pthread_join(&writer_pid, NULL);
    for(int i = 0; i < 5; i++)
        pthread_join(&reader_pid[i], NULL);

    return 0;
}