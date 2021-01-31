#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);

void (*ssu_func)(int);

int main(void)
{
	ssu_func = signal(SIGINT, ssu_signal_handler); //ssu_func 함수를 설정함
	//SIGINT에 대한 핸들러를 지정함
	while(1) {
		printf("process running...\n");
		sleep(1);
	} //1초 마다 process running을 출력하면서 프로그램을 무한루프 시킴

	exit(0);
}

void ssu_signal_handler(int signo) { //SIGINT가 프로세스로 넘겨졌는지 확인하는 함수
	printf("SIGINT 시그널 발생\n");
	printf("SIGINT를 SIG_DFL로 재설정 함.\n");
	signal(SIGINT, ssu_func); //시그널 핸들러를 이전의 것으로 되돌림
}

