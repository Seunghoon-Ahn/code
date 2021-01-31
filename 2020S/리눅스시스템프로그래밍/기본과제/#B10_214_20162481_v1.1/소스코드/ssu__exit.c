#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Good afternoon?");
	_exit(0); //버퍼를 비우지 않고 바로 프로그램 종료
} //printf가 출력되지 않음
