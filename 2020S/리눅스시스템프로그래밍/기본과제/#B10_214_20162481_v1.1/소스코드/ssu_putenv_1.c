#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ssu_addone(void);

extern char **environ;
char glob_var[] = "HOBBY=swimming";

int main(void)
{
	int i;

	for(i = 0; environ[i] != NULL; i++)
		printf("environ[%d] : %s\n", i, environ[i]);
	//환경 변수 출력
	putenv(glob_var); //새 환경 변수 등록
	ssu_addone(); // 지역변수를 환경 변수에 출력
	printf("My hobby is %s\n", getenv("HOBBY")); //환경 변수 출력
	printf("My lover is %s\n", getenv("LOVER")); //지역 변수에서 추가한 환경 변수는 적용 안됨
	strcpy(glob_var+6, "fishing"); // 환경 변수 수정

	for(i = 0; environ[i] != NULL; i++)
		printf("environ[%d] : %s\n", i, environ[i]);
	//전체 환경 변수 출력
	exit(0); //프로그램 종료
}

void ssu_addone(void) {
	char auto_var[10];

	strcpy(auto_var, "LOVER=js");
	putenv(auto_var); //지역 변수에서 환경 변수 추가
}

