#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) 
{
	char *fname = "ssu_test.txt";
	int fd;

	if((fd = creat(fname, 0666)) < 0) {
		printf("creat error for %s\n", fname);
		exit(1);
	}
	//파일을 생성하고 0666 권한을 부여함
	//파일 디스크립터는 fd에 저장함
	//파일 생성에 실패하였을 경우 오류메시지 출력후 종료
	printf("First printf is on the screen.\n"); //표준 출력에 문장 출력
	dup2(fd, 1); //표준출력의 파일 디스크립터를 fd로 복사함
	printf("Second printf is in this file.\n");
	//표준출력에 출력하려는 것이 fd에 연결된 파일에 출력됨
	//fd에 연결된 파일을 확인하면 그 파일에 문장이 출력되어있음
	exit(0);
}

