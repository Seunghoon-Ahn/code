#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>

static void ssu_alarm(int signo);
static void ssu_func(int signo);
void ssu_mask(const char *str);

static volatile sig_atomic_t can_jump;
static sigjmp_buf jump_buf;

int main(void)
{
	if(signal(SIGUSR1, ssu_func) == SIG_ERR) { //SIGUSR1의 핸들러 함수 설정
		fprintf(stderr, "SIGUSR! error");
		exit(1);
	}

	if(signal(SIGALRM, ssu_alarm) == SIG_ERR) { //SIGALRM의 핸들러 함수 설정
		fprintf(stderr, "SIGALRM error");
		exit(1);
	}

	ssu_mask("starting main: ");

	if(sigsetjmp(jump_buf, 1)) { //jump의 도착지 설정
		ssu_mask("ending main: ");
		exit(0);
	}

	can_jump = 1;

	while(1)
		pause();

	exit(0);
}

void ssu_mask(const char *str) {
	sigset_t sig_set;
	int err_num;

	err_num = errno;

	if(sigprocmask(0, NULL, &sig_set) < 0) { //시그널 마스크를 NULL로 설정
		printf("sigprocmask() error");
		exit(1);
	} //에러시 오류 출력 후 프로그램 종료

	printf("%s", str);
	if(sigismember(&sig_set, SIGINT)) //시그널 집합에서 SIGINT 포함 확인
		printf("SIGINT ");
	if(sigismember(&sig_set, SIGQUIT)) //시그널 집합에서 SIGQUIT 포함 확인
		printf("SIGQUIT ");
	if(sigismember(&sig_set, SIGUSR1)) //시그널 집합에서 SIGUSR1 포함 확인
		printf("SIGUSR1 ");
	if(sigismember(&sig_set, SIGALRM)) //시그널 집합에서 SIGALRM 포함 확인
		printf("SIGALRM ");
	printf("\n");
	errno = err_num;
}

static void ssu_func(int signo) {
	time_t start_time;

	if(can_jump == 0)
		return;

	ssu_mask("starting ssu_func: "); //함수 호출
	alarm(3); //3초후 SIGALRM 설정
	start_time = time(NULL); //현재시간 저장

	while(1)
		if(time(NULL) > start_time + 5)
			break; //5초 흐름 확인

	ssu_mask("ending ssu_func: ");
	can_jump = 0;
	siglongjmp(jump_buf, 1); //setjmp로 점프함
}

static void ssu_alarm(int signo) { //SIGALRM의 핸들러 함수
	ssu_mask("in ssu_alarm: ");
}
