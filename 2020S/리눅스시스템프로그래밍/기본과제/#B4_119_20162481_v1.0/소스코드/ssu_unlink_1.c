#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char *fname = "ssu_dump.txt";

	if(open(fname, O_RDWR) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	} //파일을 읽기쓰기 가능하게 오픈함, 실패시 오류 메시지 출력후 프로그램 종료

	if(unlink(fname) < 0) {
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	} //파일을 unlink함, 실패시 오류메시지 출력 후 프로그램 종료

	printf("File unlinked\n"); //파일 언링크됨
	sleep(20); //20초 대기
	printf("Done\n"); //20초 흐름 확인
	exit(0);
}
