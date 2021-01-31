#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t pendingset;
	sigset_t sig_set;
	int count = 0;

	sigfillset(&sig_set); //모든 시그널을 sig_set에 추가함
	sigprocmask(SIG_SETMASK, &sig_set, NULL); //모든 시그널을 블락시킴

	while(1) { //무한 루프
		printf("count: %d\n", count++);
		sleep(1);
		
		if(sigpending(&pendingset) == 0) {
			if(sigismember(&pendingset, SIGINT)) {
				printf("SIGINT가 블록되어 대기 중, 무한 루프를 종료.\n");
				break;
			} //펜딩된 시그널 중에 SIGINT가 포함되어 있는 지 판단함
		}//펜딩중인 목록에 SIGINT가 포함되어 있다면 break함
	}

	exit(0); //프로그램 종료
}
