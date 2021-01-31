#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define MSG "message will be written to Terminal\n"

int main(void)
{
	int new_fd;

	if((new_fd = fcntl(STDOUT_FILENO, F_DUPFD, 3)) == -1) { //
		fprintf(stderr, "Error : Copying File Descriptor\n");
		exit(1);
	} //표준 출력을 파일 디스크립터 3번에 복사함

	close(STDOUT_FILENO); //표준 출력을 닫음
	write(3, MSG, strlen(MSG)); //3번 디스크립터 = 표준 출력
	exit(0);
}

