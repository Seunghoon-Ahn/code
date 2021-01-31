#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	printf("Process ID		= %d\n", getpid()); //현재 프로세스 ID 출력
	printf("Parent process ID	= %d\n", getppid()); //부모 프로세스 ID 출력
	printf("Real user ID		= %d\n", getuid()); //실제 사용자 ID 출력
	printf("Effective user ID	= %d\n", geteuid());// 유효 사용자 ID 출력
	printf("Real group ID		= %d\n", getgid()); //실제 그룹 사용자 ID 출력
	printf("Effective group ID	= %d\n", getegid()); //유효 그룹 사용자 ID 출력
	exit(0);
}
