#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	char *fname = "ssu_test.txt"; //상대경로로 파일 지정, 현재 디렉터리에 파일 생성
	int fd;  // File Descriptor 저장하는 변수

	if((fd = creat(fname, 0666)) < 0) {
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}
	//creat() 함수를 통해 파일을 0666권한으로 생성함 
	//생성에 실패하는 경우 에러 메시지 출력 후 프로그램 종료
	else {
		close(fd);  //File Descriptor를 이용하여 생성하여 불러온 파일을 닫음
		fd = open(fname, O_RDWR);   //open() 함수를 이용하여 파일을 읽기쓰기가 가능한 상태로 불러옴
		printf("Succeeded!\n<%s> is new readable and writable\n", fname);
		//파일 오픈에 성공한 경우 성공 문구와 파일읽기쓰기가 가능한 상태임을 알림
	}

	exit(0);  // 프로그램 종료
}
