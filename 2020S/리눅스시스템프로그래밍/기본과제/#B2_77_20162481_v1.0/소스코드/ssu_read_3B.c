#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) 
{
	char character;
	int fd;
	int line_count = 0;

	if((fd = open("ssu_test.txt", O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", "ssu_test.txt");
		exit(1);
	} //ssu_test 파일을 읽기 전용으로 오픈함
	//오픈시 fd에 파일 디스크립터를 저장하고, 실패시 에러메시지 출력 후 프로그램 종료

	while(1) {
		if(read(fd, &character, 1) > 0) {
			if(character == '\n')
				line_count++;
		}
		else
			break;
	} //무한 루프 속에서 파일의 개행 문자 갯수를 셈
	//파일의 줄 갯수를 line_count에 저장함

	printf("Total line : %d\n", line_count); //파일의 줄 수 출력
	exit(0);
}

