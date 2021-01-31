#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
	sigset_t set;

	sigemptyset(&set); //시그널 셋을 초기화함
	sigaddset(&set, SIGINT); //시그널 셋에 SIGINT를 추가함
	switch(sigismember(&set, SIGINT))
	{ //시그널 셋에 SIGINT가 포함되어 있는가
		case 1 : //포함되어있을때
			printf("SIGINT is included. \n");
			break;
		case 0 : //포함되어 있지 않을때
			printf("SIGINT is not included. \n");
			break;
		default : //sigismember 호출 실패일때
			printf("failed to call sigismember() \n");
	}

	switch(sigismember(&set, SIGSYS))
	{ //시그널 셋에 SIGSYS가 포함되어 있는가
		case 1 : //포함 되어 있을 때
			printf("SIGSYS is included. \n");
			break;
		case 0 : //포함 되어 있지 않을 때
			printf("SIGSYS is not included. \n");
			break;
		default : //sigismember를 실패했을때
			printf("failed to call sigismember() \n");
	}

	exit(0);
}
