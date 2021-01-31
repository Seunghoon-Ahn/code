#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *fname = "ssu_test.txt";
	char *mode = "r";

	if(fopen(fname, mode) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	} //fopen함수를 통해 파일을 읽기 모드로 오픈함
	// 실패시 에러 메시지 출력 후 프로그램 종료
	else
		printf("Success!\nFilename: <%s>, mode: <%s>\n", fname, mode);
	//파일 오픈 성공시 파일의 이름과 오픈한 모드를 출력함
	exit(0);
}

