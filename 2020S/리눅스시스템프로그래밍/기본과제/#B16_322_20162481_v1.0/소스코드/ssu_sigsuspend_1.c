#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t old_set;
	sigset_t sig_set;

	sigemptyset(&sig_set); //sig_set 초기화
	sigaddset(&sig_set, SIGINT); //SIGINT를 sig_set에 포함시킴
	sigprocmask(SIG_BLOCK, &sig_set, &old_set); 
	//sig_set에 포함된것을 블락하고, 기존 시그널 셋을 old_set에 저장
	sigsuspend(&old_set); //old_set에 포함된 시그널이 입력될때까지 프로세스 중지
	exit(0);
}
