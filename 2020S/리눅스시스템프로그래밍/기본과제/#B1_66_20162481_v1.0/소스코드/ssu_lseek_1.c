#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	char *fname = "ssu_test.txt"; //불러오고자 하는 파일의 상대경로
	off_t fsize; //파일의 크기를 저장하는 함수
	int fd; //파일의 File Descriptor 저장을 위한 변수
	
	if((fd = open(fname, O_RDONLY)) < 0) {
		fprintf(stderr, "open error for%s\n", fname);
		exit(1);
	}
	//파일을 읽기 가능한 상태로 불러옴. 오픈에 실패할 경우 에러 메시지를 출력하고 프로그램 종료

	if((fsize = lseek(fd, (off_t)0, SEEK_END)) < 0) {
		fprintf(stderr, "lseek error\n");
		exit(1);
	}
	//lseek() 함수를 통해 offset의 위치를 파일의 가장 마지막으로 옮김
	//실패할 경우 에러메시지를 출력하고 프로그램 종료

	printf("The size of <%s> is %ld bytes.\n", fname, fsize);
	//fsize의 값을 통해 파일의 크기를 바이트 단위로 확인함
	exit(0); //프로그램 종료
}

