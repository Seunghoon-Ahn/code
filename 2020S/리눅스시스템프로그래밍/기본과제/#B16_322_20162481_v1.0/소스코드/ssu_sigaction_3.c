#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

int main(void)
{
	struct sigaction act_int, act_quit;

	act_int.sa_handler = ssu_signal_handler1; //핸들러함수 지정
	sigemptyset(&act_int.sa_mask); //act_int 마스크 초기화
	sigaddset(&act_int.sa_mask, SIGQUIT); //SIGQUIT를 마스크에 추가
	act_quit.sa_flags = 0; //플래그 0으로 설정

	if(sigaction(SIGINT, &act_int, NULL) < 0) {
		fprintf(stderr, "sigaction(SIGINT) error\n");
		exit(1);
	} //SIGINT에 대한 액션으로 act_int를 설정함, 실패시 에러 출력 후 종료

	act_quit.sa_handler = ssu_signal_handler2; //act_quit의 핸들러 함수 설정
	sigemptyset(&act_quit.sa_mask); //마스크 초기화
	sigaddset(&act_quit.sa_mask, SIGINT); //SIGINT를 마스크에 추가함
	act_int.sa_flags = 0; //플래그 0으로 설정
	if(sigaction(SIGQUIT, &act_quit, NULL) < 0) {
		fprintf(stderr, "sigaction(SIGQUIT) error\n");
		exit(1);
	} //SIGQUIT에 대한 액션으로 act_quit을 설정함

	pause(); //일시정지
	exit(0);
}

static void ssu_signal_handler1(int signo) {
	printf("Signal handler of SIGINT : %d\n", signo);
	printf("SIGQUIT signal is blocked : %d\n", signo);
	printf("sleeping 3 sec\n");
	sleep(3);
	printf("Signal handler of SIGINT ended\n");
} //SIGINT가 입력되었을때의 핸들러 함수

static void ssu_signal_handler2(int signo) {
	printf("Signal handler of SIGQUIT : %d\n", signo);
	printf("SIGINT signal is blocked : %d\n", signo);
	printf("sleeping 3 sec\n");
	sleep(3);
	printf("Signal handler of SIGQUIT ended\n");
} //SIGQUIT이 입력되었을 때의 핸들러 함수
