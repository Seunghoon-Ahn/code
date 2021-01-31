#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_loop1(void *arg);
void *ssu_loop2(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 변수의 초기화
int shared_value;

int main(void)
{
	pthread_t tid1, tid2;
	int status;

	shared_value = 0; //공유할 변수 선언

	if(pthread_create(&tid1, NULL, ssu_loop1, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //tid1에 ssu_loop1함수를 새 쓰레드로 실행

	sleep(1);

	if(pthread_create(&tid2, NULL, ssu_loop2, NULL) != 0) {
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	} //tid2에 ssu_loop2 함수를 새 쓰레드로 실행

	if(pthread_join(tid1, (void *)&status) != 0) {
		fprintf(stderr, "pthread_join error\n");
		exit(1);
	} //tid1이 실행되는 동안 대기

	if(pthread_join(tid2, (void *)&status) != 0) {
		fprintf(stderr, "pthread_join error\n");
		exit(1);
	} //tid2가 실행되는 동안 대기
	//tid1 tid2가 번갈아 실행되게 함
	status = pthread_mutex_destroy(&mutex); //뮤텍스 변수의 해제
	printf("code = %d\n", status);
	printf("programming is end\n");
	exit(0);
}

void *ssu_loop1(void *arg) {
	int i;

	for(i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex); //뮤텍스 변수에 독립적으로 사용
		printf("loop1 : %d\n", shared_value);
		shared_value++;

		if(i == 10)
			return NULL;

		pthread_mutex_unlock(&mutex); //뮤텍스 변수 독립사용 해제
		sleep(1);
	}

	return NULL;
}

void *ssu_loop2(void *arg) {
	int i;

	for(i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex); //뮤텍스 변수 독립사용
		printf("loop2 : %d\n", shared_value);
		shared_value++;
		pthread_mutex_unlock(&mutex); //뮤텍스 변수 독립사용 해제
		sleep(2);
	}

	return NULL;
}
