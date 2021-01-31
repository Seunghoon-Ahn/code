#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	
	if(argc < 2) {
		fprintf(stderr, "usage : %s <file1> <file2> .. <fileN>\n", argv[0]);
		exit(1);
	} //인자가 잘못 입력되었을 경우, 사용법을 출력하고 프로그램 종료

	for(i = 1; i <argc; i++) {
		if(access(argv[i], F_OK) < 0) {
			fprintf(stderr, "%s doesn't exist.\n", argv[i]);
			continue;
		} //access 함수로 파일의 존재 여부 확인

		if(access(argv[i], R_OK) == 0)
			printf("User can read %s\n", argv[i]);
		//access 함수로 파일 읽기 가능 여부 확인
		if(access(argv[i], W_OK) == 0)
			printf("User can write %s\n", argv[i]);
		//access 함수로 파일 쓰기 가능 여부 확인
		if(access(argv[i], X_OK) == 0)
			printf("User can write %s\n", argv[i]);
	}	//access 함수로 파일 실행 가능 여부 확인

	exit(0);
}
