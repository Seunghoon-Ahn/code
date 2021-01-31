#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CREAT_MODE (S_IRUSR | S_IRGRP | S_IROTH)
//사용자의 읽기쓰기, 그룹사용자의 읽기, 다른 사용자의 읽기 권한을 지정함

char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
	char *fname = "ssu_hole.txt"; //파일명, 상대경로, 현재 디렉터리에 파일 생성
	int fd;

	if((fd = creat(fname, CREAT_MODE)) < 0) {
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}
	//creat() 함수를 이용하여 파일을 생성함, 생성에 실패하였을 경우, 에러 메시지 출력 후 프로그램 종료

	if(write(fd, buf1, 12) != 12) {
		fprintf(stderr, "buf1 write error\n");
		exit(1);
	}
	//파일의 초기 offset인 파일의 시작부터 buf1의 데이터를 씀
	//쓰기에 실패했을 경우 에러 메시지 출력 후 프로그램 종료
	if(lseek(fd, 15000, SEEK_SET) < 0) {
		fprintf(stderr, "lseek error\n");
		exit(1);
	}
	//파일의 offset을 15000바이트 이동함
	//offset 이동에 실패하였을 경우 에러 베시지 출력 후 프로그램 종료

	if(write(fd, buf2, 12) != 12) {
		fprintf(stderr, "buf2 write error\n");
		exit(1);
	}
	//파일의 offset 위치부터 buf2의 데이터를 쓰기작업 함
	//쓰기에 실패하였을 경우 에러 메시지 출력 후 프로그램 종료
	exit(0); //최종 프로그램 종료
}

