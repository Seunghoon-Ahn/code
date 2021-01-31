#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

static void ssu_func(int signo);
void ssu_print_mask(const char *str);

int main(void)
{
	sigset_t new_mask, old_mask, wait_mask;
	ssu_print_mask("Program start: ");
	if(signal(SIGINT, ssu_func) == SIG_ERR) {
		fprintf(stderr, "signal(SIGINT) error\n");
		exit(1);
	} //SIGINT의 핸들러 함수 지정, 실패 시 오류 출력 후 프로그램 종료

	sigemptyset(&wait_mask); //wait_mask 초기화
	sigaddset(&wait_mask, SIGUSR1); //wait_mask에 SIGUSR1 추가
	sigemptyset(&new_mask); //new_mask 초기화
	sigaddset(&new_mask, SIGINT); //new_mask에 SIGINT 추가

	if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
		fprintf(stderr, "SIG_BLOCK() error\n");
		exit(1);
	} //new_mask에 있는 시그널을 블록으로 지정, 기존의 시그널 셋은 old_mask에 저장

	ssu_print_mask("in critical region: ");

	if(sigsuspend(&wait_mask) != -1) {
		fprintf(stderr, "sigsuspend() error\n");
		exit(1);
	}//wait_mask에 있는 시그널이 입력될때까지 일시정지

	ssu_print_mask("after return from sigsuspend: ");

	if(sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
		fprintf(stderr, "SIG_SETMASK() error\n");
		exit(1);
	} //old_mask에 있는 시그널 셋을 블록함

	ssu_print_mask("program exit: ");
	exit(0);
}

void ssu_print_mask(const char *str) {
	sigset_t sig_set;
	int err_num;
	err_num = errno;

	if(sigprocmask(0, NULL, &sig_set) < 0) {
		fprintf(stderr, "sigprocmask() error\n");
		exit(1);
	} //블록된 시그널을 해제함

	printf("%s", str);

	if(sigismember(&sig_set, SIGINT))
		printf("SIGINT ");
	if(sigismember(&sig_set, SIGQUIT))
		printf("SIGQUIT ");
	if(sigismember(&sig_set, SIGUSR1))
		printf("SIGUSR1 ");
	if(sigismember(&sig_set, SIGALRM))
		printf("SIGALRM ");
	// sig_set에 위의 시그널이 존재하는지를 확인함
	printf("\n");
	errno = err_num;
}

static void ssu_func(int signo) {
	ssu_print_mask("\nin ssu_func: ");
}
