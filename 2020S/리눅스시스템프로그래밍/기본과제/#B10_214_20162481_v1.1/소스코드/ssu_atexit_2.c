#include <stdio.h>
#include <stdlib.h>

void ssu_out(void);

int main(void)
{
	if(atexit(ssu_out)) { //종료 후 ssu_out이 실행되도록 함
		fprintf(stderr, "atexit error\n");
		exit(1);
	} //실패시 에러 출력

	exit(0); //프로그램 종료
}

void ssu_out(void) { //ssu_out이 출력할 문구 지정
	printf("atexit succeeded!\n");
}
