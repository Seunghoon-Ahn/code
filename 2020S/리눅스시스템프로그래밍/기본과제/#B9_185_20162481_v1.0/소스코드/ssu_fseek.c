#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	FILE *fp;
	long position;
	int character;

	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, " fopen error for %s\n", fname);
		exit(1);
	} //파일을 읽기 모드로 오픈, 실패시 에러 출력 후 프로그램 종료

	printf("Input number >>");
	scanf("%ld", &position); //position을 입력받음
	fseek(fp, position-1, SEEK_SET); //position번쨰의 위치로 fp를 이동함
	character = getc(fp); //문자 1개를 읽어서 character에 저장
	printf("%ldth character => %c\n", position, character); //읽어온 문자 출력
	exit(0); //프로그램 종료
}

