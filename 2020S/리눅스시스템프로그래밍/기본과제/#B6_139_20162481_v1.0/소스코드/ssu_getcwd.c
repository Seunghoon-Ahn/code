#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_MAX 1024

int main(void) {
	char *pathname;

	if(chdir("/home/oslab") < 0) {
		fprintf(stderr, "chdir error\n");
		exit(1);
	} //
	//현재 작업 디렉터리를 /home/oslab으로 변경, 실패시 에러 출력 후 종료
	pathname = malloc(PATH_MAX); //문자열을 저장할 공간 동적할당
	if(getcwd(pathname, PATH_MAX) == NULL) {
		fprintf(stderr, "getcwd error\n");
		exit(1);
	} //getcwd()함수로 현재 작업 디렉터리를 불러와 pathname에 저장함

	printf("current directory = %s\n", pathname); //현재 작업 디렉터리 출력
	exit(0); //프로그램 종료
}
