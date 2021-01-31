#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define MODE_EXEC (S_IXUSR | S_IXGRP | S_IXOTH)

int main(int argc, char *argv[])
{
	struct stat statbuf;
	int i;
	if(argc < 2) {
		fprintf(stderr, "usage : %s <file1> <file2> ... <fileN>\n", argv[0]);
		exit(1);
	} //인자가 적게 입력되었을 경우, 사용자에게 사용법 출력 후 프로그램 종료

	for(i = 1; i < argc; i++) {
		if(stat(argv[i], &statbuf) < 0) {
			fprintf(stderr, "%s : stat error\n", argv[i]);
			continue;
		} //인자 마다 각각의 파일 정보를 불러와서 statbuf에 저장, 실패시 에러 출력 후 종료
		statbuf.st_mode != MODE_EXEC; //유저, 그룹, 다른 사용자의 실행 권한을 반전시킴
		statbuf.st_mode ^= (S_IXGRP | S_IXOTH); //그룹, 다른 사용자의 실행 권한을 XOR 시킴

		// 파일의 권한을 chmod() 함수를 통해 설정한 값으로 부여함
		if(chmod(argv[i], statbuf.st_mode) < 0) //실패시 에러 출력
			fprintf(stderr, "%s : chmod error\n", argv[i]);
		else
			printf("%s : file permission was changed.\n",argv[i]);
	}
	exit(0);
}

