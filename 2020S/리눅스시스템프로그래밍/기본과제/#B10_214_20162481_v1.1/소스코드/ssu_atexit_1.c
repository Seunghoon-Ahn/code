#include <stdio.h>
#include <stdlib.h>

static void ssu_exit1(void);
static void ssu_exit2(void);

int main(void)
{
	if(atexit(ssu_exit2) != 0) {
		fprintf(stderr, "atexit error for ssu_exit2");
		exit(1);
	} //메인 함수 종료 후 실행할 함수 지정1

	if(atexit(ssu_exit1) != 0) {
		fprintf(stderr, "atexit error for ssu_exit1");
		exit(1);
	} //메인 함수 종료 후 실행할 함수 지정2

	if(atexit(ssu_exit1) != 0) {
		fprintf(stderr, "atexit error for ssu_exit1");
		exit(1);
	} // 메인 함수 종료 후 실행할 함수 지정3

	printf("done\n");
	exit(0);
} // 메인 함수 종료 후 지정한 함수를 역순으로 실행함 3 -> 2 -> 1

static void ssu_exit1(void) {
	printf("ssu_exit1 handler\n");
}

static void ssu_exit2(void) {
	printf("ssu_exit2 handler\n");
}

