#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	int a, b;
	int i;

	setbuf(stdin, buf); //표준 입력의 버퍼를 buf로 설정
	scanf("%d %d", &a, &b);//문자들을 입력함

	for(i = 0; buf[i] != '\n'; i++)
		putchar(buf[i]);//버퍼에서 개행문자 전까지 한문자씩 출력함

	putchar('\n'); //개행 문자 출력
	exit(0); //프로그램 종료
}
