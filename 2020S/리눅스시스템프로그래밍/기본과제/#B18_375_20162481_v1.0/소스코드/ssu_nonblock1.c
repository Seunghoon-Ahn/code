#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

void set_flags(int fd, int flags);
void clr_flags(int fd, int flags);

char buf[500000];

int main(void)
{
	int ntowrite, nwrite;
	char *ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf)); //표준입력해서 읽음
	fprintf(stderr, "reading %d bytes\n", ntowrite);
	set_flags(STDOUT_FILENO, O_NONBLOCK); //표준 출력에 논블록 설정

	ptr = buf;
	while(ntowrite > 0) {
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite); //표준 출력에 쓰기
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

		if(nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	clr_flags(STDOUT_FILENO, O_NONBLOCK); //표준 출력의 플래그 초기화
	exit(0);
}

void set_flags(int fd, int flags) {
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0) {
		fprintf(stderr, "fcntl F_GETFL failed");
		exit(1);
	} //파일의 접근권한과 상태플래그를 리턴

	val |= flags; //flags를 켬

	if(fcntl(fd, F_SETFL, val) < 0) {
		fprintf(stderr, "fcntl F_SETFL failed");
		exit(1);
	} //파일 상태 플래그를 val로 설정
}

void clr_flags(int fd, int flags) {
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0) {
		fprintf(stderr, "fcntl F_GETFL failed");
		exit(1);
	} //파일의 상태 플래그를 저장

	val &= ~flags; //flags를 제외함

	if(fcntl(fd, F_SETFL, val) < 0) {
		fprintf(stderr, "fcntl F_SETFL failed");
		exit(1);
	} //파일의 상태플래그를 val로 설정
}

