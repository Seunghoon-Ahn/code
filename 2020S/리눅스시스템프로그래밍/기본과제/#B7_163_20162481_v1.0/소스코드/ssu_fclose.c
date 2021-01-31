#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	FILE *fp; //파일 구조체 포인터

	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	} //fp에 파일을 오픈함, 실패시 에러 메시지 출력 후 프로그램 종료
	else {
		printf("Success!\n");
		printf("Opening \"%s\" in \"r\" mode!\n", fname);
	} //파일 오픈 성공시, 성공 문구, 파일 이름, 오픈 모드를 출력함

	fclose(fp); //파일을 닫음(저장도 이루어짐)
	exit(0);//프로그램 종료
}
