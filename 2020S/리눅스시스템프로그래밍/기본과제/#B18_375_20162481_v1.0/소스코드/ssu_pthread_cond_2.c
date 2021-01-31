#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int glo_val1 = 1, glo_val2 = 2;

void *ssu_thread1(void *arg);
void *ssu_thread2(void *arg);

int main(void)
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, ssu_thread1, NULL);
	//ssu_thread1 함수를 새 쓰레드로 생성
	pthread_create(&tid2, NULL, ssu_thread2, NULL);
	//ssu_thread2 함수를 새 쓰레드로 생성
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	//tid1 tid2 가 서로 번갈아 실행될 수 있도록 함
	pthread_mutex_destroy(&lock); //lock에 있는 뮤텍스 변수를 해제
	pthread_cond_destroy(&cond); // cond에 있는 조건 변수를 해제

	exit(0);
}

void *ssu_thread1(void *arg) {
	sleep(1);
	glo_val1 = 2;
	glo_val2 = 1;

	if(glo_val1 > glo_val2)
		pthread_cond_broadcast(&cond); //ssu_thread2를 실행가능상태로 변경시킴

	printf("ssu_thread1 end\n");
	return NULL;
}

void *ssu_thread2(void *arg) {
	struct timespec timeout;
	struct timeval now;

	pthread_mutex_lock(&lock); //뮤텍스 변수 독립사용을 위해 잠금설정
	gettimeofday(&now, NULL);

	timeout.tv_sec = now.tv_sec +5;
	timeout.tv_nsec = now.tv_usec * 1000;

	if(glo_val1 <= glo_val2) {
		printf("ssu_thread2 sleep\n");
		if(pthread_cond_timedwait(&cond, &lock, &timeout) ==ETIMEDOUT)
			//함수를 대기상태로 전환
			printf("timeout\n");
		else
			printf("glo_val1 = %d, glo_val2 = %d\n", glo_val1, glo_val2);
	} //if문 내의 pthread_cond_timedwait는 리턴되지 않음

	pthread_mutex_unlock(&lock); //lock 뮤텍스 변수 해제
	printf("ssu_thread end\n");
	return NULL;
}


