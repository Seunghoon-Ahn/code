#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int fd;
	int length;

	if((fd = open(fname, O_RDONLY, 0644)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}
	//파일을 읽기 전용으로 오픈 하고 파일 디스크립터 값을 fd에 저장
	//실패 시 오류메시지 출력 후 프로그램 종료
	if(dup2(1, 4) != 4) {
		fprintf(stderr, "dup2 call failed\n");
		exit(1);
	}
	//표준 출력의 파일 디스크립터를 4번으로 복사한다
	while(1) {
		length = read(fd, buf, BUFFER_SIZE);

		if(length <= 0) //파일의 끝에 닿으면 무한루프 종료
			break;

		write(4, buf, length);
	} //4번 파일 디스크립터를 인자로 하여 write를 호출함
	//4번과 1번이 연결되어있기에, 표준 출력에 쓰는 것과 같음
	exit(0);
}

