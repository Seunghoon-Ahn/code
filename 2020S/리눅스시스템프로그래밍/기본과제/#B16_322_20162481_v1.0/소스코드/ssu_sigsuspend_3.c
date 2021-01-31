#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void ssu_signal_handler(int signo);
void ssu_timestamp(char *str);

int main(void)
{
	struct sigaction sig_act;
	sigset_t blk_set;

	sigfillset(&blk_set); //모든 시그널을 blk_set에 추가
	sigdelset(&blk_set, SIGALRM); //SIGALRM을 시그널 셋에서 해제
	sigemptyset(&sig_act.sa_mask); //시그널 마스크 해제
	sig_act.sa_flags = 0; //시그널 플래그 0으로 설정
	sig_act.sa_handler = ssu_signal_handler; //시그널 핸들러 함수 지정
	sigaction(SIGALRM, &sig_act, NULL); //SIGALRM일 경우 sig_act 실행
	ssu_timestamp("before sigsuspend()"); //현재 시간 함수 호출
	alarm(5); //5초 후 SIGALRM 설정
	sigsuspend(&blk_set); //blk_set에 포함된 시그널은 모두 펜딩시킴
	ssu_timestamp("after sigsuspend()"); //현재 시간 함수 호출
	exit(0);
}

void ssu_signal_handler(int signo) {
	printf("in ssu_signal_handler() function\n");
} //시그널 핸들러 함수

void ssu_timestamp(char *str) {
	time_t time_val;

	time(&time_val);
	printf("%s the time is %s\n", str, ctime(&time_val));
}//현재시간 출력 함수
