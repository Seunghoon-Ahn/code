#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	char *fname = "ssu_test.txt"; //상대경로를 통해 현재 디렉터리에서 파일 탐색
	int fd;  //File Descriptor를 저장하는 변수 선언

	if((fd = creat(fname, 0666)) < 0) {     //fname을 가진 파일을 생성함, 권한은 모두가 읽고 쓸수 있도록 지정
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}
	//파일을 생성하는데에 실패 했을 경우, 에러 메시지를 출력하고 프로그램을 종료함

	else {
		printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd);
		close(fd);
	}
	//파일 생성에 성공하였을 경우, 성공 문구와 파일의 이름, 파일의 File Descriptor를 출력함
	exit(0); //프로그램 종료
}
