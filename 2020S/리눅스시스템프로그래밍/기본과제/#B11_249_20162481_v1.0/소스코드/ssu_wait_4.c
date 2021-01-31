#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child1, child2;
	int pid, status;

	if((child1 = fork()) == 0)
		execlp("date", "date", (char *)0);
	//child1을 통해 date 명령어 수행
	if((child2 = fork()) == 0)
		execlp("who", "who", (char *)0);
	//child2를 통해 who 명령어 수행
	printf("parent: waiting for children\n");
	// 부모 프로세스가 wait 상태임을 표시
	while((pid = wait(&status)) != -1) {
		if(child1 == pid) //child1의 status를 출력함
			printf("parent: first child: %d\n", (status >> 8));
		if(child2 == pid) //child2의 status를 출력함
			printf("parent: second child: %d\n", (status >> 8));
	}
	
	printf("parent: all children terminated\n"); //자식프로세스가 모두 종료됨을 표시
	exit(0); //프로그램 종료
}
