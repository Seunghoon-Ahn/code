#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	if(fork() == 0)
		execl("/bin/echo", "echo", "this is", "message one", (char *)0);
	//자식 프로세스에서 메시지 출력
	if(fork() == 0)
		execl("/bin/echo", "echo", "this is", "message two", (char *)0);
	//자식 프로세스에서 2번째 메시지 출력
	printf("parent: waiting for children\n");
	//부모 프로세스에서 wait 상태임을 출력
	while(wait((int *)0) != -1);
	//자식 프로세스가 종료 되기를 기다림
	printf("parent: all children terminated\n"); //자식 프로세스가 종료됨을 알림
	exit(0); //프로그램 종료
}
