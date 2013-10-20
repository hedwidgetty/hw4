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
	pthread_t pro1, con1, pro2, con2, pro3, con3, pro4, con4, pro5, con5;
	pthread_mutex_init(&theMutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	
	printf("Creating Consumer1\n");
	pthread_create(&con1, NULL, consumer, NULL);

	printf("Creating Producer1\n");
	pthread_create(&pro1, NULL, producer, NULL);

	printf("Creating Consumer2\n");
	pthread_create(&con2, NULL, consumer, NULL);

	printf("Creating Producer2\n");
	pthread_create(&pro2, NULL, producer, NULL);

	printf("Creating Consumer3\n");
	pthread_create(&con3, NULL, consumer, NULL);

	printf("Creating Producer3\n");
	pthread_create(&pro3, NULL, producer, NULL);

	printf("Creating Consumer4\n");
	pthread_create(&con4, NULL, consumer, NULL);

	printf("Creating Producer4\n");
	pthread_create(&pro4, NULL, producer, NULL);

	printf("Creating Consumer5\n");
	pthread_create(&con5, NULL, consumer, NULL);

	printf("Creating Producer5\n");
	pthread_create(&pro5, NULL, producer, NULL);
	
	
	printf("Executing Producer1\n");
	pthread_join(pro1, 0);
	printf("Executing Consumer1\n");
	pthread_join(con1, 0);

	printf("Executing Producer2\n");
	pthread_join(pro2, 0);
	printf("Executing Consumer2\n");
	pthread_join(con2, 0);

	printf("Executing Producer3\n");
	pthread_join(pro3, 0);
	printf("Executing Consumer3\n");
	pthread_join(con3, 0);

	printf("Executing Producer4\n");
	pthread_join(pro4, 0);
	printf("Executing Consumer4\n");
	pthread_join(con4, 0);

	printf("Executing Producer5\n");
	pthread_join(pro5, 0);
	
	printf("Executing Consumer5\n");
	pthread_join(con5, 0);

	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	
	pthread_mutex_destroy(&theMutex);
	
	return 0;
}
