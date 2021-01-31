#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	int val;

	fd = open("exec_copy.txt", O_CREAT); //파일을 오픈함, 파일이 없는 경우 생성
	execl("/home/seunghun/loop", "./loop", NULL); //루프 프로그램을 실행함
	exit(0);
}

