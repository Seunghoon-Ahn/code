#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define VALUE_DONE 10
#define VALUE_STOP1 3
#define VALUE_STOP2 6

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *ssu_thread1(void *arg);
void *ssu_thread2(void *arg);

int glo_val = 0;

int main(void)
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, &ssu_thread1, NULL);
	pthread_create(&tid2, NULL, &ssu_thread2, NULL);
	//ssu_thread1, ssu_thread2를 새 쓰레드로 각각 실행
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	//각각의 쓰레드를 번갈아서 실행함
	//<<pthread_mutex_destroy(), pthread_cond_destory() 함수 호출 없음>>
	printf("final value: %d\n", glo_val);
	exit(0);
}

void *ssu_thread1(void *arg) {
	while(1) {
		pthread_mutex_lock(&lock); //뮤텍스 변수 독립사용
		pthread_cond_wait(&cond, &lock); //시그널이 오기 전까지 블록상태로 만듬
		glo_val++;
		printf("global value ssu_thread1: %d\n", glo_val);
		pthread_mutex_unlock(&lock); //독립사용 해제

		if(glo_val >= VALUE_DONE)
			return NULL;
	}
}

void *ssu_thread2(void *arg) {
	while(1) {
		pthread_mutex_lock(&lock); //뮤텍스 변수 독립 사용
		if(glo_val < VALUE_STOP1 || glo_val > VALUE_STOP2)
			pthread_cond_signal(&cond); //glo_val 값에 따라 시그널을 보냄
		else { //또는 본인이 출력함
			glo_val++;
			printf("global value ssu_thread2: %d\n", glo_val);
		}

		pthread_mutex_unlock(&lock); //뮤텍스 변수 독립사용 해제

		if(glo_val >= VALUE_DONE)
			return NULL;
	}
}
