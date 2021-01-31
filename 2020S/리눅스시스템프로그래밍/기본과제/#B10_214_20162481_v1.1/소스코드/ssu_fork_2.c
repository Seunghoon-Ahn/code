#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	char character, first, last;
	long i;

	if((pid = fork()) > 0) {
		first = 'A';
		last = 'Z';
	} //부모프로세스는 A~Z
	else if (pid == 0) {
		first = 'a';
		last = 'z';
	} //자식 프로세스는 a~z
	else {
		fprintf(stderr, "%s\n", argv[0]);
		exit(1);
	}

	for(character = first; character <= last; character++) {
		for(i = 0; i <= 100000; i++)
			;
		write(1, &character, 1);
	} //한글자씩 출력함

	printf("\n");
	exit(0);
}
