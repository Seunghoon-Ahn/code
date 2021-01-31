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

	if((fd1 = open(fname, O_RDONLY, 0644)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}
	//fname의 파일을 644 권한과 읽기 전용으로 오픈함 
	//실패시 에러메시지를 출력후 프로그램 종료
	
	fd2 = dup(fd1); //fd1의 파일 디스크립터를 fd2로 복사함
	count = read(fd1, buf, 12); //fd1이 가리키는 파일에서 12바이트만큼 읽어서 buf로 복사
	buf[count] = 0; //문자열의 마지막을 나타내기 위해 널문자 입력
	printf("fd1's printf : %s\n", buf); //buf에 있는 내용 출력
	lseek(fd1, 1, SEEK_CUR); // 개행 문자를 lseek으로 넘어감
	count = read(fd2, buf, 12); //fd2를 이용하여 12바이트만큼 파일을 읽어옴
	buf[count] = 0; //문자열의 마지막을 나타내기 위해 널문자 입력
	printf("fd2's printf : %s\n", buf); // buf에 있는 내용 출력
	exit(0);
}
