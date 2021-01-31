#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid;
	pid_t pid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //새 쓰레드 생성, 쓰레드 생성 후 ssu_thread 실행, 오류시 종료

	pid = getpid(); //기존 쓰레드에서의 pid
	tid = pthread_self(); //기존 쓰레드에서의 tid
	printf("Main Thread: pid %u tid %u \n", (unsigned int)pid, (unsigned int)tid);
	sleep(1); //1초 일시정지
	exit(0);
}

void *ssu_thread(void *arg) { //새 쓰레드에서 작동될 함수
	pthread_t tid;
	pid_t pid;

	pid = getpid(); //새 쓰레드에서의 pid
	tid = pthread_self(); //새 쓰레드 에서의 tid
	printf("New Thread: pid %d tid %u \n", (int)pid, (unsigned int)tid);
	return NULL;
}
