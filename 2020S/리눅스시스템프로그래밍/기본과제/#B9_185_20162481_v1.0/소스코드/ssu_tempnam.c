#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *arg_directory = NULL;
	char *arg_prefix = NULL;

	if(argc != 3) {
		fprintf(stderr, "usage: %s <directory> <prefix>\n", argv[0]);
		exit(1);
	}
	// 인자가 적게 입력된 경우 사용법을 출력하고 프로그램 종료
	arg_directory = argv[1][0] != ' ' ? argv[1] : NULL; //임시 파일의 디렉터리 지정
	arg_prefix = argv[2][0] != ' ' ? argv[2] : NULL; //임시 파일 이름의 접두어 지정
	printf("created : %s\n", tempnam(arg_directory, arg_prefix)); //임시 파일 생성
	exit(0); //프로그램 종료
}
