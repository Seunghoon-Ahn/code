#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;

	for(i = 0; i < argc; i++)
		printf("argv[%d] : %s\n", i, argv[i]);
	//argv로 입력된 것을 순서대로 출력함
	exit(0); //프로그램 종료
}
