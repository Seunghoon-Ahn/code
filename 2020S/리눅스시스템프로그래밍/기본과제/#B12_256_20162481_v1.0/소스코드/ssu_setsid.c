#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} // fork 실패시 에러 출력 후 프로그램 종료
	else if (pid != 0)
		exit(1); //자식 프로세스가 아닌 경우 프로세스 종료
	
	printf("before pid = %d, sid = %d\n", getpid(), getsid(getpid()));
	//setsid 전의 프로세스 ID와 세션 ID를 출력함
	setsid(); //자식 프로세스에서 setsid를 호출하여 세선 리더 프로세스를 생성함
	printf("after pid = %d, sid = %d\n", getpid(), getsid(getpid()));
	//setsid 이후의 프로세스 ID와 세션 ID를 출력함
	exit(0); //프로그램 종료
}
