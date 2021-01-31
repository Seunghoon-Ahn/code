#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char glob_str[] = "write to standard output\n";
int glob_val = 10;

int main(void)
{
	pid_t pid;
	int loc_val;
	loc_val = 100;
	if(write(STDOUT_FILENO, glob_str, sizeof(glob_str)-1) != sizeof(glob_str) -1) {
		fprintf(stderr, "write error\n");
		exit(1);
	} //표준 출력에 문장 출력, 실패 시 에러 출력 후 종료

	printf("before fork\n");

	if((pid = fork()) < 0) { //fork 시도, 실패 시 에러 출력 후 종료
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if ( pid == 0) { //자식 프로세스일때, 값을 증가시킴
		glob_val++;
		loc_val++;
	}
	else //부모 프로세스 일때, 3초 일시정지
		sleep(3);

	printf("pid = %d, glob_val = %d, loc_val = %d\n", getpid(), glob_val, loc_val);
	exit(0); //변수 값 출력 후 종료
}
