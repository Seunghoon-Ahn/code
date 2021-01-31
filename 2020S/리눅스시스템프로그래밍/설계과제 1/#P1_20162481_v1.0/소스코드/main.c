#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "ssu_score.h"

#define SECOND_TO_MICRO 1000000 // 1초는 백만마이크로초

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);

int main(int argc, char *argv[])
{
	struct timeval begin_t, end_t;
	gettimeofday(&begin_t, NULL); //시작시간 저장

	ssu_score(argc, argv);

	gettimeofday(&end_t, NULL); //끝시간 저장
	ssu_runtime(&begin_t, &end_t); //시간계산, 끝시간 - 처음 시간

	exit(0); //프로그램 종료
}

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t)
{ 
	end_t->tv_sec -= begin_t->tv_sec; //끝난 시간에서 처음시간을 뺌

	if(end_t->tv_usec < begin_t->tv_usec){
		end_t->tv_sec--;
		end_t->tv_usec += SECOND_TO_MICRO;
	} //나중의 us값이 작을경우 1초를 뺴서 us값이 더해줌

	end_t->tv_usec -= begin_t->tv_usec;
	printf("Runtime: %ld:%06ld(sec:usec)\n", end_t->tv_sec, end_t->tv_usec);
} //프로그램 총 소요시간 계산 후 출력하는 함수
