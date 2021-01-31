#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <termios.h>

int main(void)
{
	pid_t sid_stderr;
	pid_t sid_stdin;
	pid_t sid_stdout;

	sid_stdin = tcgetsid(STDIN_FILENO);
	//stdin의 세션 리더 ID를 불러와 변수에 저장함
	if(sid_stdin == -1) {
		fprintf(stderr, "tcgetsid error\n");
		exit(1);
	} //tcgetsid 실패시 오류 출력 후 프로그램 종료
	else
		printf("Session Leader for stdin: %d\n", sid_stdin);
	//tcgetsid 성공시 stdin의 세션 리더 ID 출력
	sid_stdout = tcgetsid(STDOUT_FILENO);
	//stdout의 세션 리더 ID를 불러와 변수에 저장함
	if(sid_stdout == -1) {
		fprintf(stderr, "tcgetsid error\n");
		exit(1);
	} //tcgetsid 실패시 오류 출력 후 프로그램 종료
	else
		printf("Session Leader for stdout: %d\n", sid_stdout);
	//tcgetsid 성공시 stdout의 세션 리더 ID를 출력
	sid_stderr = tcgetsid(STDERR_FILENO);
	//stderr 의 세션 리더 ID를 불러와 변수에 저장함
	if(sid_stderr == -1) {
		fprintf(stderr, "tcgetsid error\n");
		exit(1);
	} //tcgetsid 실패시 오류 출력 후 프로그램 종료
	else
		printf("Session Leader for stderr: %d\n", sid_stderr);
	//tcgetsid 성공시 stderr의 세선 리더 ID를 출력함
	exit(0); //프로그램 종료
}

