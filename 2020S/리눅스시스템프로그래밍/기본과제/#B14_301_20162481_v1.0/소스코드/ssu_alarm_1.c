#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);

int count = 0;

int main(void)
{
	signal(SIGALRM, ssu_signal_handler); //SIGARM이 전달되었을때의 핸들러 함수 지정
	alarm(1); //1초 후 SIGARM 전달

	while(1); //무한루프 만들기

	exit(0);
}

void ssu_signal_handler(int signo) {
	printf("alarm %d\n", count++); //현재 알람 출력
	alarm(1); //새로운 알람 설정
} //함수로 인해서 매 1초 마다 알람이 울리게 됨

