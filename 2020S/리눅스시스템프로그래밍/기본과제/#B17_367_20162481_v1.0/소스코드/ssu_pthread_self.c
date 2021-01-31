#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //새 쓰레드를 생성하여 ssu_Thread 실행

	printf("%u\n", (unsigned int)tid); //tid 출력

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //새 쓰레드를 생성하여 ssu_thread 실행

	printf("%u\n", (unsigned int)tid); //tid 출력
	sleep(1); //1초 일시정지
	exit(0);
}

void *ssu_thread(void *arg) { //새 쓰레드에서 실행하는 함수
	pthread_t tid;
	tid = pthread_self(); //현재 쓰레드의 tid를 얻어옴
	printf("->%u\n", (unsigned int)tid); //현재 쓰레드의 tid 출력
	return NULL;
}
