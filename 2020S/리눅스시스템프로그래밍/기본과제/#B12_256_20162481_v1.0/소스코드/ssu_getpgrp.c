#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pgid;
	pid_t pid;

	pid = getpid(); // 프로세스 ID를 저장
	pgid = getpgrp(); //프로세스 그룹 ID를 저장
	printf("pid: %d, pgid: %d\n", pid, pgid); //저장한 ID들을 출력함
	exit(0); //프로그램 종료
}
