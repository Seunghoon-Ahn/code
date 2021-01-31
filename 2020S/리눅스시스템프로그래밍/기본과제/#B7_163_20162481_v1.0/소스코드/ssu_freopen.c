#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void) {
	char *fname = "ssu_test.txt";
	int fd;

	printf("First printf : Hello, OSLAB!!\n");
	//프로그램의 시작을 printf로써 확인할수 있게 함
	if((fd = open(fname, O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	} //open 함수로 파일을 오픈함, 실패시 에러 출력 후 종료

	if(freopen(fname, "w", stdout) != NULL)
		printf("Second printf : Hello, OSLAB!!\n");
	//freopen함수를 이용하여 파일을 재오픈함
	//실패 시에는 표준 출력을 파일에 쓰지 않음
	//파일 재오픈에 성공하였을 경우, w 옵션이므로 파일은 초기화됨
	//표준 출력으로 나가려던 printf 문장이 파일에 쓰이게됨
	exit(0);
}
