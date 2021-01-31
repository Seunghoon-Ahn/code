#include <stdio.h>
#include <stdlib.h>

void ssu_printenv(char *label, char ***envpp);

extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
	ssu_printenv("Initially", &envp); //초기값 출력
	putenv("TZ=PST8PDT"); //timezone 환경변수 추가
	ssu_printenv("After changing TZ", &envp); //변경 이후의 환경 변수 출력
	putenv("WARNING=Don't use envp after putenv()");//환경 변수 추가
	ssu_printenv("After setting a new variable", &envp); //환경 변수 출력
	printf("value of WARNING is %s\n", getenv("WARNING")); //WARNING 환경 변수 출력
	exit(0); //프로그램 종료
}

void ssu_printenv(char *label, char ***envpp) {
	char **ptr;
	printf("----%s----\n", label); //첫줄 출력
	printf("envp is at %8o and contains %8o\n", envpp, *envpp); //환경 변수의 위치 출력
	printf("environ is at %8o and contains %8o\n", &environ, environ); //환경 변수의 메모리 위치 출력
	printf("My environment variable are:\n");

	for(ptr = environ; *ptr; ptr++)
		printf("(%8o) = %8o -> %s\n", ptr, *ptr, *ptr);
	//환경 변수 출력
	printf("(%8o) = %8o -> %s\n", ptr, *ptr, *ptr);
}
