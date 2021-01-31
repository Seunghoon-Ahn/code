#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char c;
	int fd;

	if((fd = open("ssu_test.txt", O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", "ssu_test.txt");
		exit(1);
	}//ssu_test 파일을 읽기 전용으로 오픈, 실패시 에러 메시지 출력 후 프로그램 종료
	//파일 디스크립터는 fd에 저장

	while(1) {
		if(read(fd, &c, 1) > 0) 
			putchar(c);
		else
			break;
	} //파일의 내용을 한글자씩 읽어 표준 출력에 출력함

	exit(0);
}

