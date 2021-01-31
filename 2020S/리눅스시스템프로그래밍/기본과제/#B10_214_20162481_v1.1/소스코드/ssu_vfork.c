#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void ssu_local_func(void);

int main(void)
{
	printf("Before vfork\n");
	ssu_local_func(); //함수 실행
	printf("After ssu_local_func, my PID is %d\n", getpid()); //프로세스 ID 출력
	exit(0);
}

void ssu_local_func(void) {
	pid_t pid;
	if((pid = fork()) == 0) //자식 프로세스일 경우 프로세스 ID 출력
		printf("I'm child. My PID is %d\n", getpid());
	else if (pid > 0)
		sleep(3); //부모 프로세스일 경우 3초 일시정지
	else
		fprintf(stderr, "vfork error\n"); // vfork 실패시 에러 출력
}
