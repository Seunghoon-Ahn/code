#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define LINE_MAX 2048

static void ssu_alarm(int signo);

int main(void)
{
	char buf[LINE_MAX];
	int n;

	if(signal(SIGALRM, ssu_alarm) == SIG_ERR) {
		fprintf(stderr, "SIGALRM error\n");
		exit(1);
	} //SIGALRM의 핸들러 함수로 ssu_alarm 지정, 에러시 오류 출력 후 종료

	alarm(10); //10초 알람 설정

	if((n = read(STDIN_FILENO, buf, LINE_MAX)) < 0) {
		fprintf(stderr, "read() error\n");
		exit(1);
	} //표준 입력에서 버퍼로 읽어옴

	alarm(0);//0초 알람 설정
	write(STDOUT_FILENO, buf, n); //표준 출력으로 버퍼에 내용을 출력
	exit(0);
}

static void ssu_alarm(int signo) { //SIGALRM 핸들러 함수
	printf("ssu_alarm() called!\n"); //알람이 울리면 출력
}

