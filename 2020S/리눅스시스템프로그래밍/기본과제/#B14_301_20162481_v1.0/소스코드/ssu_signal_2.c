#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void ssu_signal_handler(int signo);

int main(void)
{
	if(signal(SIGINT, ssu_signal_handler) == SIG_ERR) {
		fprintf(stderr, "cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	} //SIGINT가 입력될 경우의 핸들러 함수 지정, 실패 시 오류 출력 후 종료

	if(signal(SIGTERM, ssu_signal_handler) == SIG_ERR) {
		fprintf(stderr, "cannot handle SIGTERM\n");
		exit(EXIT_FAILURE);
	} //SIGTERM이 입력될 경우 핸들러 함수 지정, 실패 시 오류 출력 후 종료

	if(signal(SIGPROF, SIG_DFL) == SIG_ERR) {
		fprintf(stderr, "cannot reset SIGPROF\n");
		exit(EXIT_FAILURE);
	} //SIGPROF를 SIG_DFL으로 등록함, SIGPROF가 입력되면 디폴트 액션을 실행

	if(signal(SIGHUP, SIG_IGN) == SIG_ERR) {
		fprintf(stderr, "cannot ignore SIGHUP\n");
		exit(EXIT_FAILURE);
	} //SIGHUP을 SIG_IGN으로 등록함, SIGHUP이 입력되면 무시

	while(1)
		pause(); //SIG가 입력될 때까지 프로그램을 pause함

	exit(0);
}

static void ssu_signal_handler(int signo) {
	if(signo == SIGINT) //SIGINT가 입력되었을 때
		printf("caught SIGINT\n"); //출력
	else if (signo == SIGTERM) //SIGTERM이 입력되었을때
		printf("caught SIGTERM\n"); //출력
	else { //그 외의 시그널이 입력된 경우
		fprintf(stderr, "unexpected signal\n");
		exit(EXIT_FAILURE);
	} //에러 출력 후 프로그램 종료

	exit(EXIT_SUCCESS);
}

