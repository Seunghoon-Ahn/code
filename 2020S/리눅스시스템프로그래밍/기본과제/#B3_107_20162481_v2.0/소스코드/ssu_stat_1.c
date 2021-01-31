#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat statbuf;

	if(argc != 2) {
		fprintf(stderr, "Usage : %s <file>\n", argv[0]);
		exit(1);
	} //인자가 적게 입력되었을 경우, 사용자에게 사용법을 출력한 후 프로그램 종료

	if((stat(argv[1], &statbuf)) < 0) {
		fprintf(stderr, "stat error\n");
		exit(1);
	} //stat 함수를 이용하여 파일에 관한 정보를 statbuf에 저장함

	printf("%s is %ld bytes\n", argv[1], statbuf.st_size);
	//저장한 파일의 정보 중에 st_size 변수로 파일 크기를 불러와 출력함
	exit(0);
}

