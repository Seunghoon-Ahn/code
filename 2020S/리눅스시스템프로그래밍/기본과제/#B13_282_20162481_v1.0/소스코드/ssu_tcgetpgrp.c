#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>

#define STDIN_NUMBER 0

static void ssu_sig_hup(int signum);
static void ssu_print_ids(char *name);

int main(void)
{
	pid_t pid;
	char character;

	ssu_print_ids("parent");
	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} //fork하여 자식 프로세스 생성, 실패시 오류 출력 후 프로그램 종료
	else if (pid > 0) {
		sleep(3);
		exit(0);
	} //부모 프로세스일 경우 3초 일시정지 후 프로그램 종료
	else { //자식 프로세스일 경우
		ssu_print_ids("child");
		signal(SIGHUP, ssu_sig_hup); //SIGNAL을 주고, SIGNAL을 받은 프로세스를 출력
		kill (getpid(), SIGTSTP); //프로세스에 SIGSTP가 전달되면 프로세스 종료
		ssu_print_ids("child");

		if(read(STDIN_FILENO, &character, 1) != 1)
			fprintf(stderr, "read error\n");
	//read를 시도함, 실패시 오류 출력
		exit(0); //프로그램 종료
	}
}

static void ssu_sig_hup(int signum) {
	printf("ssu_SIG_HUP received, pid = %d\n", getpid());
} //SIG를 받은 프로세스의 번호를 출력함

static void ssu_print_ids(char *name) {
	printf("[%s] : pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
			name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_NUMBER));
	fflush(stdout);
} //프로세스의 ID, 부모 프로세스의 ID, 프로세스 그룹 ID, 
  //foreground 프로세스 그룹 ID 출력, 출력 후 출력 버퍼 비움
	
