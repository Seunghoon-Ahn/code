#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_check_pending(int signo, char *signame);
void ssu_signal_handler(int signo);

int main(void)
{
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask); //시그널의 마스크를 초기화함
	sig_act.sa_flags = 0; //플래그를 0으로 설정
	sig_act.sa_handler = ssu_signal_handler; //sig_act에 대한 핸들러 함수 설정

	if(sigaction(SIGUSR1, &sig_act, NULL) != 0) { //SIGUSR1에 대한 검사 수행
		fprintf(stderr, "sigaction() error\n");
		exit(1);
	}
	else {
		sigemptyset(&sig_set); //sig_set을 초기화함
		sigaddset(&sig_set, SIGUSR1); //sig_set에 SIGUSR1 추가

		if(sigprocmask(SIG_SETMASK, &sig_set, NULL) != 0) {
			fprintf(stderr, "sigprocmask() error\n");
			exit(1);
		} //sig_set에 포함되어있는 시그널을 마스크함
		else {
			printf("SIGUSR1 signals are now blocked\n");
			kill(getpid(), SIGUSR1); //kill을 통해 SIGUSR1 발생시킴
			printf("after kill()\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1"); //시그널이 펜딩되어있는지 확인
			sigemptyset(&sig_set); //sig_set 초기화
			sigprocmask(SIG_SETMASK, &sig_set, NULL);
			//sig_set에 포함된 시그널을 마스크함
			printf("SIGUSR1 signals are no longer blocked\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1"); //시그널이 펜딩되어있는지 확인
		}
	}
	exit(0);
}

void ssu_check_pending(int signo, char *signame) {
	//펜딩된 시그널을 파악하는 함수
	sigset_t sig_set;

	if(sigpending(&sig_set) != 0) //펜딩되어있는지 확인이 안될때
		printf("sigpending() error\n");
	else if (sigismember(&sig_set, signo)) //펜딩 되어 있을때
		printf("a %s signal is pending\n", signame);
	else //펜딩 되어있지 않을때
		printf("%s signals are not pending\n", signame);
}

void ssu_signal_handler(int signo) { //시그널 핸들러 함수
	printf("in ssu_signal_handler function\n");
}
