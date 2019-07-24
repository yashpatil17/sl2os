#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

void *thread_producer_function(void *arg);
void *thread_consumer_function(void *arg);

sem_t full_sem;
sem_t empty_sem;
pthread_mutex_t lock;
#define MAX_SIZE 10
int buffer[MAX_SIZE];
int front,rare;

int main() 
{
	int res1,res2;
	pthread_t a_thread[MAX_SIZE],b_thread[MAX_SIZE];
	void *thread_result;
	front=0,rare=0;
	
	res1 = sem_init(&empty_sem, 0, MAX_SIZE);
	if (res1 != 0)
	 {
		perror("Semaphore empty initialization failed”");
		exit(EXIT_FAILURE);
	}
	res2 = sem_init(&full_sem, 0, 0);
	if (res2 != 0) 
	{
		perror("Semaphore full initialization failed”");
		exit(EXIT_FAILURE);
	}
	int prod,cons;
	printf("ENTER NUMBER OF PRODUCERS :\n");
	scanf("\t%d",&prod);
	printf("ENTER NUMBER OF CONSUMERS :\n");
	scanf("\t%d",&cons);
	printf("\n");
	
	int i,j;
	while(1)
	{
	for(i=0;i<prod;i++)
	{
		if(pthread_create(&a_thread[i], NULL, thread_producer_function,(void *)i+1) != 0)
			printf("\nCannot create thread.\n");
		else
		{
			
		}
	}
	
	//printf("“\nWaiting for producer thread to finish...\n”");
	
	for(i=0;i<cons;i++)
	{
		if(pthread_create(&b_thread[i], NULL, thread_consumer_function,(void *)i+1) != 0)
			printf("\nCannot create thread.\n");
		else
		{
			
		}
	}
	int res;
	//printf("“\nWaiting for consumer thread to finish...\n”");
	for(i=0;i<prod;i++)
	{
		res = pthread_join(a_thread[i], &thread_result);
		if (res != 0) 
		{
			perror("“Thread join failed”");
			exit(EXIT_FAILURE);
		}
		else{}
			//printf("“Thread joined\n”");
	}
	for(i=0;i<cons;i++)
	{
		res = pthread_join(b_thread[i], &thread_result);
		if (res != 0) 
		{
			perror("“Thread join failed”");
			exit(EXIT_FAILURE);
		}
		else{}
			//printf("Thread joined\n");
	}
	front=0,rare=0;
	
}
sem_destroy(&empty_sem);
sem_destroy(&full_sem);
exit(EXIT_SUCCESS);
}
void *thread_producer_function(void *arg)
{
	int i;
	int no=(int *)arg;
	while(1)
	{
		i=rand()%10;
		sem_wait(&empty_sem);
		pthread_mutex_lock(&lock);
		printf("\n producer no. : %d and has produced : %d",no,i);
		buffer[rare]=i;
		rare=rare+1;
		printf("\nQUEUE IS :");
		
		for(int j=front;j<rare;j++)
			printf("\t%d",buffer[j]);
			//sleep(2);
			
		sleep(rand()%7);
		pthread_mutex_unlock(&lock);
		sem_post(&full_sem);	
		pthread_exit(NULL);
	}
}
void *thread_consumer_function(void *arg)
{
	int i;
	int no=(int *)arg;
	while(1)
	{
		sem_wait(&full_sem);
		pthread_mutex_lock(&lock);
		printf("\n consumer no. : %d and has consumed : %d",no,buffer[front]);
		front=front+1;
		printf("\nQUEUE IS :");

		for(int j=front;j<rare;j++){
			printf("\t%d",buffer[j]);
			}
			//sleep(2);
		sleep(rand()%7);
		pthread_mutex_unlock(&lock);
		sem_post(&empty_sem);	
		pthread_exit(NULL);
	}
}
