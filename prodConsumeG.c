#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define N 4

int x=0;
sem_t theMutex;
sem_t empty;
sem_t full;


void removeItem(int item)
{
	printf("Removing %d\n", item);
}

void insertItem(int item)
{
	printf("Inserting %d\n", item);

}

int produce()
{
	x++;
	printf("Producing %d\n", x-1);
	return x-1;
}

int consume()
{
	x--;
	printf("Consuming %d\n", x);
	return x;
}

void* producer()
{
	int item;
	while(1)
	{
		item=produce();
		sem_wait(&empty);
		sem_wait(&theMutex);
		insertItem(item);
		sem_post(&theMutex);
		sem_post(&full);
	}
	
}


void* consumer()
{
	int item;
	while(1)
	{
		item=consume();
		sem_post(&empty);
		sem_wait(&theMutex);
		removeItem(item);
		sem_post(&theMutex);
		sem_wait(&full);
	}


	

}


int main()
{
	pthread_t pro, con;
	sem_init(&theMutex, 1, 1);
	sem_init(&empty, 1, N);
	sem_init(&full, 1, 0);
	
	printf("Creating Consumer\n");
	pthread_create(&con, NULL, consumer, NULL);

	printf("Creating Producer\n");
	pthread_create(&pro, NULL, producer, NULL);
	
	
	printf("Executing Producer\n");
	pthread_join(pro, 0);
	printf("Executing Consumer\n");
	pthread_join(con, 0);

	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&theMutex);
	
	return 0;
}
