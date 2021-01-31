#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include "zemaphore.h"

#define NUM_THREADS 3
#define NUM_ITER 10

SSU_Sem child[NUM_THREADS];
void* justprint(void* data)
{
	int thread_id = *((int*)data);
	
	for (int i = 0; i < NUM_ITER; i++)
	{
		SSU_Sem_down(&child[thread_id]); // 동작 전 잠근다.
		// 외부에서 동작이 풀리면 Thread 동작 수행
		printf("This is thread %d\n", thread_id);
		SSU_Sem_up(&child[(thread_id + 1) % NUM_THREADS]); // 동작 후 다음 Thread를 풀어준다.
	}
	return 0;
}

int main(int argc, char* argv[])
{
	pthread_t mythreads[NUM_THREADS];
	int mythread_id[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		SSU_Sem_init(&child[i], 0); // Thread별로 semaphore 객체 초기화
		mythread_id[i] = i;
		pthread_create(&mythreads[i], NULL, justprint, (void*)&mythread_id[i]);
	}
	SSU_Sem_up(&child[0]); // 처음 Thread를 깨운다.

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(mythreads[i], NULL);
	}

	return 0;
}
