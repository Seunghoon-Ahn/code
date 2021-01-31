#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_alarm(int signo);

int main(void)
{
	printf("Alarm Setting\n"); //프로그램의 시작
	signal(SIGALRM, ssu_alarm); //SIGALRM의 핸들러 함수를 ssu_alarm으로 지정
	alarm(2); //2초 알람 설정

	while(1) {
		printf("done\n");
		pause(); //시그널이 들어올때까지 멈춤
		alarm(2); //시그널이 들어온 후 다시 2초 알람 설정
	} //무한 반복

	exit(0);
}

void ssu_alarm(int signo) {
	printf("alarm..!!!\n");
} //SIGALRM의 핸들러 함수

