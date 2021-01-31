#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

void ssu_setbuf(FILE *fp, char *buf);

int main(void) {
	char buf[BUFFER_SIZE];
	char *fname = "/dev/pts/1";
	FILE *fp;

	if((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}//dev/pts/19를 표준출력으로 사용하기 위해 오픈함

	ssu_setbuf(fp, buf);//라인 버퍼로 fp에 사용할 버퍼 지정
	fprintf(fp, "Hello, "); // 버퍼에 저장
	sleep(1);
	fprintf(fp, "UNIX!!"); // 버퍼에 저장
	sleep(1);
	fprintf(fp, "\n"); // 개행문자가 입력되었을 때, 버퍼에서 파일로 씀
	sleep(1);
	ssu_setbuf(fp, NULL); //버퍼를 NULL로 설정
	fprintf(fp, "HOW"); //버퍼 없이 바로 파일에 씀
	sleep(1);
	fprintf(fp, " ARE"); //바로 파일에 씀
	sleep(1);
	fprintf(fp, " YOU?"); //바로 파일에 씀
	sleep(1);
	fprintf(fp, "\n"); //바로 파일에 씀
	sleep(1);
	exit(0); //프로그램 종료
}

void ssu_setbuf(FILE *fp, char *buf) {
	size_t size;
	int fd;
	int mode;

	fd = fileno(fp);
	if(isatty(fd)) //fd가 터미널에 연결되어 있으면
		mode = _IOLBF; //라인버퍼 설정
	else
		mode = _IOFBF;//아닐 경우 풀 버퍼 설정

	if(buf == NULL) { //버퍼가 NULL일 경우
		mode = _IONBF; //버퍼 없음
		size = 0; //버퍼 크기는 0
	}
	else //버퍼가 있을 경우 사이즈는 1024
		size = BUFFER_SIZE;
	//파일에 맞게 버퍼길이와 모드를 설정함
	setvbuf(fp, buf, mode, size);
}
