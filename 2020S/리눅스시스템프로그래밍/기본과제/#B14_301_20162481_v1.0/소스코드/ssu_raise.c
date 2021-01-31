#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void ssu_signal_handler1(int signo);
void ssu_signal_handler2(int signo);

int main(void)
{
	if(signal(SIGINT, ssu_signal_handler1) == SIG_ERR) {
		fprintf(stderr, "cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}//SIGINT가 입력되면 작동할 핸들러 함수 등록

	if(signal(SIGUSR1, ssu_signal_handler2) == SIG_ERR) {
		fprintf(stderr, "cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	} //SIGUSR1이 전달되면 작동할 핸들러 함수 등록

	raise(SIGINT); //자기 자신에게 SIGINT 전달
	raise(SIGUSR1); //자기 자신에게 SIGUSR1 전달
	printf("main return\n");
	exit(0);
}

void ssu_signal_handler1(int signo) {
	printf("SIGINT 시그널 발생\n");
} //SIGINT의 핸들러 함수

void ssu_signal_handler2(int signo) {
	printf("SIGUSR1 시그널 발생\n");
} //SIGUSR1의 핸들러 함수

