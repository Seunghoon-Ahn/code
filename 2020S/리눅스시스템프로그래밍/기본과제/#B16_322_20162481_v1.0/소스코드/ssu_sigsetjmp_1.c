#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void ssu_signal_handler(int signo);

jmp_buf jump_buffer;

int main(void)
{
	signal(SIGINT, ssu_signal_handler); //시그널 핸들러 함수 설정

	while(1) {
		if(setjmp(jump_buffer) == 0) { //점프 도착 위치 설정
			printf("Hit Ctrl-c at anytime ... \n");
			pause(); //일시정지
		}
	}

	exit(0);
}

void ssu_signal_handler(int signo) { //시그널 핸들러 함수
	char character;

	signal(signo, SIG_IGN); //핸들러로 입력된 시그널을 무시함
	printf("Did you hit Ctrl-c?\n" "Do you really want to quit? [y/n] ");
	character = getchar(); //글자 하나 입력받음

	if(character == 'y' || character == 'Y')
		exit(0); //y가 입력되면 종료
	else {//SIGINT가 입력되면 핸들러 함수가 호출되도록 함
		signal(SIGINT, ssu_signal_handler);
		longjmp(jump_buffer, 1); //setjmp위치로 넘어감
	}
}

