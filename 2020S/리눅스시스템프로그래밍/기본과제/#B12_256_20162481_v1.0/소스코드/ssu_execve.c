#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"ssu_execl_test_1", "param1", "param2", (char *)0};
	//인자를 설정함
	char *env[] = {
		"NAME = value",
		"nextname=nextvalue",
		"HOME=/home/oslab",
		(char *)0
	}; //환경 변수를 설정함

	printf("this is the original program\n");
	execve("./ssu_execl_test_1", argv, env); 
	//execve를 통해 프로세스를 실행함, argv를 인자로, env를 환경 변수로 사용함
	printf("%s\n", "This ine should never get printed\n");
	exit(0);
}
