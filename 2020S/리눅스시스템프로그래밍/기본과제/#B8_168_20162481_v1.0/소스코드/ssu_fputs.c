#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	FILE *fp;
	if(argc != 2) {
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}//인자가 적게 입력되었을 경우 오류 메시지 출력 후 종료
	if((fp = fopen(argv[1], "w+")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);//실패시 오류 출력 후 종료
	}//인자로 입력받은 파일을 쓰기모드로 오픈함
	fputs("Input String >> ", stdout); //표준 출력에 문구 출력
	gets(buf);//표준 입력에 입력된 것을 buf로 받아옴
	fputs(buf, fp); //버퍼에 있는 것을 파일에 출력함
	rewind(fp); //파일의 처음으로 이동
	fgets(buf, sizeof(buf), fp); //파일의 처음부터 버퍼 크기만큼 읽어옴
	puts(buf);//표준 출력에 버퍼 출력
	fclose(fp); //파일 저장 및 종료
	exit(0); //프로그램 종료
}
