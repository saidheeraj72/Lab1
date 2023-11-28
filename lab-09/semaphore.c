// Roll No.: CS21B2019
// Name: Devarakonda SLR Siddesh
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t s1, s2;

void *threadA()
{
    sem_wait(&s2);
    printf("A1\n");
    sem_post(&s1);
    sem_wait(&s2);
    printf("A2\n");
    sem_post(&s1);
}

void *threadB()
{
    sem_wait(&s1);
    printf("B1\n");
    sem_post(&s2);
    sem_wait(&s1);
    printf("B2\n");
    sem_post(&s2);
}

int main()
{
    pthread_t tA, tB;
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);

    pthread_create(&tA, NULL, &threadA, NULL);
    pthread_create(&tB, NULL, &threadB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    return 0;
}