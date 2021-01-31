#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 8

struct thread_data {
	int thread_index;
	int sum;
	char *message;
};

void *ssu_printhello(void *arg);

struct thread_data thread_data_array[THREAD_NUM];
char *messages[THREAD_NUM];

int main(void)
{
	pthread_t tid[THREAD_NUM];
	int sum;
	int i;
	
	sum = 0;
	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvytye, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";
	
	for(i = 0; i < THREAD_NUM; i++) { //각각의 문장에 대해 쓰레드 생성
		sum = sum +i;
		thread_data_array[i].thread_index = i;
		thread_data_array[i].sum = sum;
		thread_data_array[i].message = messages[i];
		printf("Creating thread %d\n", i);

		if(pthread_create(&tid[i], NULL, ssu_printhello,
					(void *)&thread_data_array[i]) != 0) {
			fprintf(stderr, "pthread_create error\n");
			exit(1);
		} //각각에 대해 ssu_printhello 함수를 새 쓰레드로 생성함
	}

	sleep(5); //5초 일시정지
	exit(0);
}

void *ssu_printhello(void *arg) {
	struct thread_data *data;
	char *message;
	int thread_index;
	int sum;

	sleep(1);
	data = (struct thread_data *)arg;
	thread_index = data -> thread_index;
	sum = data->sum;
	message = data -> message;
	printf("Thread %d: %s Sum=%d\n", thread_index, message, sum);
	return NULL;
} //새 쓰레드에서 작동하는 함수

