#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	extern char **environ; //환경 변수
	char **str;
	int i;

	for(i = 0; i < argc; i++) //실행시 주어진 인자 출력
		printf("argv[%d]: %s\n", i, argv[i]);

	for(str = environ; *str != 0; str++)
		printf("%s\n", *str); //환경 변수 출력

	exit(0);
}