#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;
	int val;

	if((fd = open("exec_copy.txt", O_CREAT)) < 0) {
		fprintf(stderr, "open error for %s\n", "exec_copy.txt");
		exit(1);
	} //파일을 오픈함
	val = fcntl(fd, F_GETFD, 0); //FD의 플래그를 val에 저장

	if(val & FD_CLOEXEC) //플래그 비트가 켜져있는지 검사
		printf("close-on-exec bit on\n");
	else
		printf("close-on-exec bif off\n");

	val |= FD_CLOEXEC; //플래그 비트를 켬

	if(val & FD_CLOEXEC) //FD_CLOEXEC 비트가 켜져있는지 검사
		printf("close-on-exec bit on\n");
	else
		printf("close-on-exec bit off\n");

	fcntl(fd, F_SETFD, val); //파일 디스크립터를 val로 설정
	execl("/home/seunghun/loop", "./loop", NULL); //루프 프로그램 실행
}
