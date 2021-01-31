#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid1, tid2;
	int thread1 = 1;
	int thread2 = 2;
	int status;

	if(pthread_create(&tid1, NULL, ssu_thread, (void *)&thread1) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //ssu_thread를 새 쓰레드로 생성함, 실패시 오류 출력 후 프로그램 종료

	if(pthread_create(&tid2, NULL, ssu_thread, (void *)&thread2) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //ssu_thread를 새 쓰레드로 생성함, 실패시 오류 출력 후 종료
	pthread_join(tid1, (void *)&status); //쓰레드의 종료를 기다림
	pthread_join(tid2, (void *)&status); //쓰레드의 종료를 기다림
	exit(0);
}

void *ssu_thread(void *arg) {
	int thread_index;
	int i;

	thread_index = *((int *)arg);

	for(i = 0; i < 5; i++) {
		printf("%d : %d\n", thread_index, i);
		sleep(1);
	} //쓰레드 번호와 5 미만까지 출력함
	 //중간에 1초 일시정지
	return NULL;
}
