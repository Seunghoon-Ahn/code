#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	
	while(fgets(buf, BUFFER_SIZE, stdin) != NULL) 
		//표준입력에서 buf로 문자를 받아옴
		if(fputs(buf, stdout) == EOF) { //fputs로 표준 출력에 출력함
			fprintf(stderr, "standard output error\n");
			exit(1);//출력 값이 없을 경우, 에러 메시지 출력 후 종료
		}

	if(ferror(stdin)) { //표준 입력에서 에러가 발견된 경우
		fprintf(stderr, "standard input error \n");
		exit(1);
	}//에러 메시지 출력 후 프로그램 종료

	exit(0); //프로그램 종료
}

