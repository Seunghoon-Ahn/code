#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>

double ssu_maketime(struct timeval *time);

void term_stat(int stat);

void ssu_print_child_info(int stat, struct rusage *rusage);

int main(void)
{
	struct rusage rusage;
	pid_t pid;
	int status;

	if((pid = fork()) == 0) { //자식 프로세스로 분기
		char *args[] = {"find", "/", "-maxdepth", "4", "-name", "stdio.h", NULL};
		if(execv("/usr/bin/find", args) < 0) { //args를 인자로 전달
			fprintf(stderr, "execv error\n");
			exit(1);
		} //execv 실패시 오류 출력 후 프로그램 종료
	}

	if(wait3(&status, 0, &rusage) == pid) //부모 프로세스는 자식 프로세스의 종료를 기다림
		ssu_print_child_info(status, &rusage);
	else {
		fprintf(stderr, "wait3 error\n");
		exit(1);
	} //wait3 실패시 오류 출력 후 프로그램 종료

	exit(0); //프로그램 종료
}

double ssu_maketime(struct timeval *time) {
	return ((double)time -> tv_sec + (double)time->tv_usec/1000000.0);
} //프로그램의 실행 시간을 초단위로 구하는 함수

void term_stat(int stat) {
	if (WIFEXITED(stat)) //자식 프로세스가 정상적으로 종료되었을 때
		printf("normally terminated. exit status = %d\n", WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat)) //자식 프로세스가 시그널을 받았지만 비정상적으로 종료되었을 때
		printf("abnormal termination by signal %d. %s\n", WTERMSIG(stat),
#ifdef WCOREDUMP //WCOREDUMP가 정의되어있을 떄
			WCOREDUMP(stat)?"core dumped":"no core" //코어덤프인지 아닌지 출력
#else
			NULL //WCOREDUMP가 없는 경우 NULL 지정
#endif
			);
	else if (WIFSTOPPED(stat)) //자식 프로세스가 중지 중일 경우
		printf("stopped by signal %d\n", WSTOPSIG(stat)); //자식 프로세스의 중지 사유를 알림
}

void ssu_print_child_info(int stat, struct rusage *rusage) {
	printf("Termination info follows\n");
	term_stat(stat);
	printf("user CPU time : %.2f(sec)\n", ssu_maketime(&rusage->ru_utime));
	printf("system CPU time : %.2f(sec)\n", ssu_maketime(&rusage->ru_stime));
} // 프로세스의 종료 사유와 프로세스의 CPU 사용시간 출력
