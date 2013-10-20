#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 4
pthread_mutex_t theMutex;
pthread_cond_t condc, condp;
int buffer=0;

void* producer(void* ptr)
{
	int x;
	for(x=0; x<=MAX; x++)
	{
		pthread_mutex_lock(&theMutex);
		printf("Producer Locked\n");
		while(buffer!=0)
		{
			printf("Producer waiting\n");
			pthread_cond_wait(&condp, &theMutex);
			
		}
		printf("Producer creating widget %d\n", x);
		buffer=x;
		printf("Signaling Consumer\n");
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&theMutex);
		printf("Producer unlocked\n");
	}
	pthread_exit(0);
}

void* consumer(void* ptr)
{
	int x;
	
	for(x=1; x<=MAX; x++)
	{
		pthread_mutex_lock(&theMutex);
		printf("Consumer locked\n");
		while(buffer==0)
		{
			printf("Consumer waiting\n");
			pthread_cond_wait(&condc, &theMutex);
			
		}
		printf("Consumer consuming widget %d\n", x);
		buffer=0;
		printf("Signaling Producer\n");
		pthread_cond_signal(&condp);
		pthread_mutex_unlock(&theMutex);
		printf("Consumer unlocked\n");
	}
	pthread_exit(0);


	

}

int main()
{
	pthread_t pro, con;
	pthread_mutex_init(&theMutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	
	printf("Creating Consumer\n");
	pthread_create(&con, NULL, consumer, NULL);

	printf("Creating Producer\n");
	pthread_create(&pro, NULL, producer, NULL);
	
	
	printf("Executing Producer\n");
	pthread_join(pro, 0);
	printf("Executing Consumer\n");
	pthread_join(con, 0);

	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&theMutex);
	
	return 0;
}
