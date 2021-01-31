#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	char name[L_tmpnam];
	FILE *fp;

	printf("Temporary filename <<%s>>\n", tmpnam(name));
	//tmp파일을 생성하고 파일 경로및 이름을 name에 저장함
	if((fp = tmpfile()) == NULL) {
		fprintf(stderr, " tmpfile create error!!\n");
		exit(1);
	} //fp에 tmp파일 생성, 실패 시 오류 출력 후 종료

	fputs("create tmpfile success!!\n", fp); //fp의 tmp파일에 문장 입력
	rewind(fp); //파일의 처음으로 offset을 옮김
	fgets(buf, sizeof(buf), fp); //buf크기만큼 파일에서 읽어옴
	puts(buf); //buf를 화면에 출력
	exit(0); //프로그램 종료
}

