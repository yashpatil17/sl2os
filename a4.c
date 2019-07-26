#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

#define buff_size 10

typedef struct {
    sem_t full,empty;
    pthread_mutex_t lock ;
    int buff[buff_size];
    int in,out;
}buffer;

buffer b;

void init()
{
    b.in=0 ; b.out=0;
    sem_init(&b.full,0,0);
    sem_init(&b.empty,0,buff_size);
    pthread_mutex_init(&b.lock,NULL);
}

void* producer (void* arg)
{
    int i = *(int*)num;
    printf("\n ------ Thread for producer %d started production \n",i);
    while(1) {
        int z=(rand()%4)+1;
        sleep(z);
        sem_wait(&b.empty);
        pthread_mutex_lock(&b.lock);
        printf("\nProducer %d produced")
    }
}