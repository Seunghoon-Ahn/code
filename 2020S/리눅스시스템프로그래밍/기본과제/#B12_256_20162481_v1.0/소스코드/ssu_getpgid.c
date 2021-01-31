#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pgid;
	pid_t pid;

	if(argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	} //인자가 부족할 경우 사용법 출력 후 프로그램 종료

	pid = getpid(); //getpid를 통해 프로세스 ID를 받아옴
	pgid = getpgid(atoi(argv[1])); //지정한 프로세스의 그룹 ID를 받아옴
	printf("pid: %d, pgid: %d\n", pid, pgid); //출력
	exit(0); //프로그램 종료
}
