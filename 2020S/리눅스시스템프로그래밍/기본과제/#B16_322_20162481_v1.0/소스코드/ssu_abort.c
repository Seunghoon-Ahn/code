#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("abort terminate this program\n");
	abort(); //스스로에게 abort 명령 실행
	printf("this line is never reached\n"); 
	//위에서 프로그램이 종료되어 출력되지 않음
	exit(0);
}

