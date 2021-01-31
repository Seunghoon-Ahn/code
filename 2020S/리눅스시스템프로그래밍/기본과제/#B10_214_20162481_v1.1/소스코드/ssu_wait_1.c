#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void ssu_echo_exit(int status);

int main(void)
{
	pid_t pid;
	int status;

	if((pid = fork()) < 0) {
		fprintf(stderr, "forck error\n");
		exit(1);
	} //fork함, 실패시 오류 출력 후 종료
	else if (pid == 0)
		exit(7);
	//자식 프로세스 일경우 종료
	if(wait(&status) != pid) {
		fprintf(stderr, "wait error\n");
		exit(1);
	} //부모 프로세스일경우 wait 함, 에러시 오류 출력 후 종료

	ssu_echo_exit(status); // 함수 호출

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} //fork함, 실패시 오류 출력 후 종료
	else if (pid == 0)
		abort();
	//자식 프로세스일 경우, abort을 통해 비정상 종료
	if(wait(&status) != pid) {
		fprintf(stderr, "wait error\n");
		exit(1);
	} // 부모 프로세스일 경우 wait함, 실패시 오류 출력 후 종료

	ssu_echo_exit(status); //함수 호출

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} //fork함, 에러시 오류 출력 후 종료
	else if (pid == 0)
		status /= 0;
	// 자식 프로세스일 경우 0으로 나눠 비정상 종료를 유도함
	if(wait(&status) != pid) {
		fprintf(stderr, "wait error\n");
		exit(1);
	} //부모 프로세스일 경우 wait함, 실패시 오류 출력 후 종료

	ssu_echo_exit(status); //함수 호출
	exit(0);
}

void ssu_echo_exit(int status) {
	if(WIFEXITED(status)) //정상 종료일 경우 정상 종료 및 시그널값 출력
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status)) //비정상 종료일 경우 각 경우에 맞게 시그널값 출력
		printf("adnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
				WCOREDUMP(status) ? " (core file generated)" : "");
#else
				"");
#endif
	else if (WIFSTOPPED(status)) //자식 프로세스가 종료된 경우 시그널값 출력
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
