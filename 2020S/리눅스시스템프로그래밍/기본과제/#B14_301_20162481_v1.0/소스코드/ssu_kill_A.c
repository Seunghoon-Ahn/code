#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "usage: %s [Process ID]\n", argv[0]);
		exit(1);
	} //인자가 적게 입력된 경우 사용법 출력 후 종료
	else
		kill(atoi(argv[1]), SIGKILL);
	//입력된 인자에 대해서 SIGKILL을 보냄
	exit(0);
}
