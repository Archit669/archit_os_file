#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <unistd.h> 


#define NUM_READERS 5
#define NUM_WRITERS 5

sem_t mutex, writeblock;
int data = 0, rcount = 0;

void *reader(void *arg)
{
    intptr_t f = (intptr_t)arg;
    sem_wait(&mutex);
    rcount++;
    if (rcount == 1)
        sem_wait(&writeblock);
    sem_post(&mutex);

    printf("Data read by the reader%ld is %d\n", f, data);
    // Simulate some processing
    sleep(1);

    sem_wait(&mutex);
    rcount--;
    if (rcount == 0)
        sem_post(&writeblock);
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *writer(void *arg)
{
    intptr_t f = (intptr_t)arg;
    sem_wait(&writeblock);
    data++;
    printf("Data written by the writer%ld is %d\n", f, data);
    // Simulate some processing
    sleep(1);
    sem_post(&writeblock);

    pthread_exit(NULL);
}

int main()
{
    pthread_t rtid[NUM_READERS], wtid[NUM_WRITERS];
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    for (intptr_t i = 0; i < NUM_WRITERS; i++)
    {
        pthread_create(&wtid[i], NULL, writer, (void *)i);
    }

    for (intptr_t i = 0; i < NUM_READERS; i++)
    {
        pthread_create(&rtid[i], NULL, reader, (void *)i);
    }

    for (intptr_t i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(wtid[i], NULL);
    }

    for (intptr_t i = 0; i < NUM_READERS; i++)
    {
        pthread_join(rtid[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeblock);

    return 0;
}
