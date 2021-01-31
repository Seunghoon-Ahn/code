#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];

	setbuf(stdout, buf);//출력을 위한 버퍼를 buf으로 설정함
	printf("Hello, ");
	sleep(1);
	printf("OSLAB!!");
	sleep(1);
	printf("\n"); //라인 버퍼를 사용하므로 개행 문자를 만난 이후
	sleep(1); //한번에 출력됨

	setbuf(stdout, NULL); //출력을 위한 버퍼를 설정하지 않고 바로 출력함
	printf("How"); //printf문들이 매 초마다 출력됨
	sleep(1);
	printf(" are"); //1초 후 출력
	sleep(1);
	printf(" you?"); //1초 후 출력
	sleep(1);
	printf("\n"); //1초 후 출력
	exit(0); //프로그램 종료
}
