#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void ssu_charactertime(char *str);

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} //fork함, 실패시 에러 출력 후 프로그램 종료
	else if(pid == 0) //자식 프로세스 일때 출력할 것
		ssu_charactertime("output from child\n");
	else //부모 프로세스 일때 출력할 것
		ssu_charactertime("output from parent\n");

	exit(0);
}

static void ssu_charactertime(char *str) {
	char *ptr;
	int print_char;

	setbuf(stdout, NULL); //버퍼링이 없어짐

	for(ptr = str; (print_char = *ptr++) != 0; ) {
		putc(print_char, stdout);
		usleep(10);
	} //자식, 부모 프로세스가 경쟁적으로 출력을 수행함
}
