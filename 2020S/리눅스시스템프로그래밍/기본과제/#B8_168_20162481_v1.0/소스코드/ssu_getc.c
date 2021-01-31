#include <stdio.h>
#include <stdlib.h>
int main(void) {
	int character;

	while((character = getc(stdin)) != EOF)
		//getc 를 통해 표준 입력에 입력을 받음
		if(putc(character, stdout) == EOF) {
			//입력받은 문자열을 putc로 표준 출력에 씀
			fprintf(stderr, "standard output error\n");
			exit(1);
		}//출력 에러시 오류 출력 후 프로그램 종료

	if(ferror(stdin)) {
		fprintf(stderr, "standard input error\n");
		exit(1);
	}//stdin에 에러가 있는 경우 에러 출력 후 프로그램 종료

	exit(0); //프로그램 종료
}
