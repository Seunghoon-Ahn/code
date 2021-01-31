#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	char *fname = "ssu_test.txt";
	//상대경로를 사용함. 현재 작업 디렉터리에서 파일을 탐색함
	int fd; //File Descriptor를 저장하기 위한 변수

	if((fd = open(fname, O_RDONLY)) < 0) {
		fprintf(stderr, "Open error for %s\n", fname);
		exit(1);
	}
	// open() 함수를 통해 읽기만 가능한 상태로 파일을 불러옴
	//파일을 오픈하지 못하거나, 생성하지 못할 경우 오류 메시지 출력
	else
		printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd);
	//파일을 오픈에 성공한 경우
	//성공 문구와 함꼐 파일의 이름과 파일의 File Descriptor를 출력함
	exit(0); //프로그램 종료
}

