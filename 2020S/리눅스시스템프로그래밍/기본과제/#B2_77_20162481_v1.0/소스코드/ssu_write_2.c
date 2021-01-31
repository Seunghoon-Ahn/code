#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define S_MODE 0644
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd1, fd2;
	int length;

	if(argc != 3) {
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	} //입력받은 인자가 적을 경우, 사용자에게 사용법을 표시하고 프로그램 종료

	if((fd1 = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}
	//fd1에 첫번째 파일을 읽기 전용으로 오픈함, 실패시 오류메시지 출력 후 종료
	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_MODE)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[2]);
		exit(1);
	}
	//fd2에 두번째 파일을 오픈함, 파일이 없을 경우 새로 생성함
	//실패시 오류메시지 출력 후 프로그램 종료
	while((length = read(fd1, buf, BUFFER_SIZE)) > 0)
		write(fd2, buf, length);
	//첫번째 파일의 끝까지 두번째 파일에 write함 
	exit(0);
}

