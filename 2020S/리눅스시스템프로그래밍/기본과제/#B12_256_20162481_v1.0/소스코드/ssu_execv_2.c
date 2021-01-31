#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"ssu_execl_test_1", "param1", "param2", (char *)0};
	//프로세스를 실행 할때 인자로 넘겨줄 것을 argv로 저장함
	printf("this is the original program\n");
	execv("./ssu_execl_test_1", argv); //execv를 통해 프로세스 실행
	printf("%s\n", "This line should never get printed");
	exit(0);
}