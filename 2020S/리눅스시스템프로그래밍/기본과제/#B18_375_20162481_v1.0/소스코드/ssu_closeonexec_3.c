#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int flag;
	if((flag = fcntl(STDOUT_FILENO, F_DUPFD)) == -1) {
		fprintf(stderr, "Error : Checking CLOSE_ON_EXEC\n");
		exit(1);
	} //fcntl의 인자가 부족함, 에러 출력후 프로그램 종료

	printf("CLOSE ON EXEC flag is = %d\n", flag);
	exit(0);
}

