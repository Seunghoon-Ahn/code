#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc!=3) {
		fprintf(stderr, "usage: %s <actualname> <symname>\n", argv[0]);
		exit(1);
	} //인자가 잘못 들어온 경우, 사용법 출력 후 프로그램 종료

	if(symlink(argv[1], argv[2]) < 0) {
		fprintf(stderr, "symlink error\n");
		exit(1);
	} //symlink() 함수를 통해 심볼릭 링크 파일을 생성함
	else //링크 생성에 성공 하면 그 링크를 출력함
		printf("symlink: %s -> %s\n", argv[2], argv[1]);
	// 실패시 오류 메시지 출력 후 프로그램 종료
	exit(0);
}
