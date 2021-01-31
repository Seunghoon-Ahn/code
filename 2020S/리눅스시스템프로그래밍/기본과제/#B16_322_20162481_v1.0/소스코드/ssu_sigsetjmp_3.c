#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

sigjmp_buf jmp_buf1;
sigjmp_buf jmp_buf2;

int main(void)
{
	struct sigaction act_sig1;
	struct sigaction act_sig2;
	int i, ret;

	printf("My PID is %d\n", getpid()); //PID 출력
	ret = sigsetjmp(jmp_buf1, 1); //돌아올 위치 설정

	if(ret == 0) { //ret가 0일때
		act_sig1.sa_handler = ssu_signal_handler1; //act_sig1의 핸들러 함수 지정
		sigaction(SIGINT, &act_sig1, NULL); //SIGINT가 입력되었을때의 행동 지정
	}
	else if(ret == 3) //ret가 3일때
		printf("----------------\n");

	printf("Starting\n");
	sigsetjmp(jmp_buf2, 2); //점프 위치 지정
	act_sig2.sa_handler = ssu_signal_handler2; //act_sig2의 핸들러 함수 지정
	sigaction(SIGUSR1, &act_sig2, NULL); //SIGUSR1이 입력되었을때의 행동 지정

	for(i = 0; i < 20; i++) {
		printf("i = %d\n", i);
		sleep(1);
	} //매 초마다 20까지 출력

	exit(0);
}

static void ssu_signal_handler1(int signo) {
	fprintf(stderr, "\nInterrupted\n");
	siglongjmp(jmp_buf1, 3); //jmp_buf1의 위치로 점프함
} //SIGINT가 입력되었을때 핸들러 함수

static void ssu_signal_handler2(int signo) {
	fprintf(stderr, "\nSIGUSR1\n");
	siglongjmp(jmp_buf2, 2); //jmp_buf2의 위치로 점프함
} //SIGUSR1이 입력되었을때 핸들러 함수
