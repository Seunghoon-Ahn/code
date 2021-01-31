#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	FILE *fp;
	long fsize;

	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	} //파일을 읽기 모드로 오픈, 실패 시 오류 출력 후 프로그램 종료

	fseek(fp, 0, SEEK_END); //파일의 끝으로 fp를 옮김
	fsize = ftell(fp); //현재 offset의 위치를 ftell로 확인
	printf("The size of <%s> is %ld bytes\n", fname, fsize);// 파일 사이즈 출력
	exit(0); //프로그램 종료
}
