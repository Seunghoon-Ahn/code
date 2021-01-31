#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	if(fork() == 0) {
		execl("/bin/echo", "echo", "this is", "message one", (char *)0);
		fprintf(stderr, "exec error\n"); //실행 실패시 오류 출력 후 종료
		exit(1);
	} // fork 하여 자식 프로세스를 만든 후 execl로 명령어를 실행함

	if(fork() == 0) {
		execl("/bin/echo", "echo", "this is", "message two", (char *)0);
		fprintf(stderr, "exec error\n"); //실행 실패시 오류 출력 후 종료
		exit(1);
	} // fork 하여 자식 프로세스를 만든 후 execl로 명령어를 실행함

	if(fork() == 0) {
		execl("/bin/echo", "echo", "this is", "message three", (char *)0);
		fprintf(stderr, "fork error\n"); //실행 실패시 오류 출력 후 종료
		exit(1);
	} // fork 하여 자식 프로세스를 만든 후 execl로 명령어를 실행함

	printf("Parent program ending\n"); //부모프로세스의 끝을 알림
	exit(0); //프로그램 종료
}