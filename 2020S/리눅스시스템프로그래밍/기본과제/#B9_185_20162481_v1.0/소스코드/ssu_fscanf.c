#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char *fname = "ssu_test.dat";
	char name[BUFFER_SIZE];
	FILE *fp;
	int age;

	fp = fopen(fname, "r"); //파일을 읽기 모드로 오픈
	fscanf(fp, "%s%d", name, &age); //이름과 나이를 읽어옴
	fclose(fp); //파일을 닫음
	fp = fopen(fname, "w"); //파일을 쓰기 모드로 오픈, w 모드이므로 파일은 초기화됨
	fprintf(fp, "%s is %d years old\n", name, age); //새로 데이터를 씀
	fclose(fp); //파일을 닫음
	exit(0); //프로그램 종료
}
