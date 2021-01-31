#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo) {
	printf("ssu_signal_handler control\n");
}

int main(void) {
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask); //sig_act의 마스크 초기화
	sig_act.sa_flags = 0; //sig_act의 플래그를 0으로 설정
	sig_act.sa_handler = ssu_signal_handler; //핸들러 함수 지정
	sigaction(SIGUSR1, &sig_act, NULL); //SIGUSR1이 발생했을때 행동 설정
	printf("before first kill()\n");
	kill(getpid(), SIGUSR1); //kill로 SIGUSR1 발동시킴
	sigemptyset(&sig_set); //sig_set 초기화
	sigaddset(&sig_set, SIGUSR1); //SIGUSR1 추가함
	sigprocmask(SIG_SETMASK, &sig_set, NULL); //sig_set에 있는 시그널을 블록함
	printf("before second kill()\n");
	kill(getpid(), SIGUSR1); //시그널 발생시킴
	printf("after second kill()\n");
	exit(0);
}
