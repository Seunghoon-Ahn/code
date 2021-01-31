#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("this is the original program\n");
	execl("./ssu_execl_test_1", "ssu_execl_test_1",
		"param1", "param2", "param3", (char *)0);
	//ssu_execl_test_1을 execl을 통해 실행하고, 프로세스에게 뒤에 나오는 인자를 넘겨줌
	printf("%s\n", "this line should never get printed\n");
	exit(0);
}