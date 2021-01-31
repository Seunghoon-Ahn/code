#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4096

int main(void)
{
	char buf[MAX_LINE];
	char name[L_tmpnam];
	FILE *fp;

	printf("temp file 1 : %s\n", tmpnam(NULL)); //임시 파일 생성
	tmpnam(name); //tmp파일 생성 후 name배열에 파일 경로 저장
	printf("temp file 2 : %s\n", name); // name에 저장된 파일 경로 출력

	if((fp = tmpfile()) == NULL) {
		fprintf(stderr, "tmpfile error\n");
		exit(1);
	} //tmpfile로 tmp파일을 생성함, 실패 시 에러 출력 후 프로그램 종료

	fputs("tmpfile created teporary file.\n", fp); //fp파일에 문장 출력
	fseek(fp, 0, SEEK_SET); //fp파일의 처음으로 offset을 보냄

	if(fgets(buf, sizeof(buf), fp) == NULL) {
		fprintf(stderr, "fgets error\n");
		exit(1);
	} //fgets를 통해 파일에서 buf만큼 읽어옴, 실패 시 에러 출력 후 종료
	fputs(buf, stdout); // 표준 출력으로 buf 출력
	exit(0); //프로그램 종료
}
