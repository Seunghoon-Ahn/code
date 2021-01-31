#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 5

void *ssu_printhello(void *arg);

int main(void)
{
	pthread_t tid[THREAD_NUM];
	int i;

	for(i = 0; i < THREAD_NUM; i++) {
		printf("In main: creating thread %d\n", i);
		
		if(pthread_create(&tid[i], NULL, ssu_printhello, (void *)&i) != 0) {
			fprintf(stderr, "pthread_create error\n");
			exit(1);
		} //THREAD_NUM만큼 ssu_printhello를 새 쓰레드로 생성
	}

	pthread_exit(NULL); //쓰레드 종료
	exit(0);
}

void *ssu_printhello(void *arg) { //새 쓰레드에서 실행되는 함수
	int thread_index;
	thread_index = *((int *)arg); //각 쓰레드의 번호를 확인함
	printf("Hello World! It's me, thread#%d!\n", thread_index);
	pthread_exit(NULL); //쓰레드 종료
	return NULL;
} 
