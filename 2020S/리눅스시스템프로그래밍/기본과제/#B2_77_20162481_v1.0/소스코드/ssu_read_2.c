#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024

int main(void) 
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int count;
	int fd1, fd2;

	fd1 = open(fname, O_RDONLY, 0644); //644권한으로 파일 오픈
	fd2 = open(fname, O_RDONLY, 0644); //644권한으로 파일 오픈
	//fd1 과 fd2는 동일한 파일의 파일 디스크립터
	if(fd1 == 0 || fd2 == 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	} //파일 오픈에 실패 했을경우 오류메시지 출력 후 프로그램 종료

	count = read(fd1, buf, 25); //fd1을 이용해 파일에서 25바이트 만큼 읽기
	buf[count] = 0; // 문자열의 마지막에 null문자 삽입
	printf("fd1`s first printf : %s\n", buf); //buf에 담긴 문자열 출력
	lseek(fd1, 1, SEEK_CUR); //개행문자를 지나칠수 있도록 offset 옮김
	count = read(fd1, buf, 24); //fd1을 이용해 파일에서 24바이트 만큼 읽기
	buf[count] = 0; //문자열의 마지막에 null문자 삽입
	printf("fd1`s second printf : %s\n", buf); //buf에 담긴 문자열 출력
	count = read(fd2, buf, 25); //fd2를 이용해 파일에서 25바이트 만큼 읽음
	buf[count] = 0; //문자열의 마지막에 null문자 삽입
	printf("fd2`s first printf : %s\n", buf); //buf에 담긴 문자열 출력
	lseek(fd2, 1, SEEK_CUR); //개행문자를 지나칠 수 있도록 offset 옮김
	count = read(fd2, buf, 24); //fd2를 이용해 파일에서 24바이트 만큼 읽음
	buf[count] = 0; //문자열의 마지막에 null문자 삽입
	printf("fd2`s second printf : %s\n", buf); //buf에 담긴 문자열 출력

	exit(0);
}
