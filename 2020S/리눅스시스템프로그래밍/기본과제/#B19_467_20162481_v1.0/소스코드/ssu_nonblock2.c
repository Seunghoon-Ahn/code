#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_CALL 100
#define MAX_BUF 20000

void serror(char *str) {
	fprintf(stderr, "%s\n", str); //표준에러에 문장 출력
	exit(1);
}

int main(void)
{
	int nread, nwrite, val, i=0;
	char *ptr;
	char buf[MAX_BUF];
	int call[MAX_CALL];

	nread = read(STDIN_FILENO, buf, sizeof(buf)); //표준입력에서 읽어 버퍼에 저장
	fprintf(stderr, "read %d bytes\n", nread); //읽은 바이트 수 출력

	if((val = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0) //파일의 상태 플래그를 val에 저장
		serror("fcntl F_SETFL error");
	val |= O_NONBLOCK; //NONBLOCK 플래그 비트를 켬
	if(fcntl(STDOUT_FILENO, F_SETFL, val) < 0) //표준 출력의 플래그를 val로 설정
		serror("fcntl F_SETFL error");

	for(ptr = buf; nread > 0; i++) {
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, nread);
		 //표준출력에 씀
		if(i < MAX_CALL)
			call[i] = nwrite;

		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if(nwrite > 0) {
			ptr += nwrite;
			nread -= nwrite;
		}
	}

	if((val = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0) //표준 출력의 플래그를 val에 저장
		serror("fcntl F_SETFL error");
	val &= ~O_NONBLOCK; //NONBLOCK 플래그 비트를 끔
	if(fcntl(STDOUT_FILENO, F_SETFL, val) < 0)
		serror("fcntl F_SETFL error");
	 //표준 출력에 val 플래그 적용
	for(i = 0; i < MAX_CALL; i++)
		fprintf(stderr, "call[%d] = %d\n", i, call[i]);

	exit(0);
}
