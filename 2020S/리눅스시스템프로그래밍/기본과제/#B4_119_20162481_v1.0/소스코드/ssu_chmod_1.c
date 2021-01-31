#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
	struct stat statbuf;
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";
	//파일 두개의 파일 포인터를 지정
	if(stat(fname1, &statbuf) < 0)
		fprintf(stderr, "stat error %s\n", fname1);
	//fname1에 대해 파일 정보를 불러와 statbuf에 저장함, 실패시 오류 출력후 종료
	if(chmod(fname1, (statbuf.st_mode & ~S_IXGRP) | S_ISUID) < 0)
		fprintf(stderr, "chmod error %s\n", fname1);
	//chmod() 함수를 통해 fname1파일에서 그룹 사용자의 실행 권한을 제거함
	if(chmod(fname2, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH) < 0)
		fprintf(stderr, "chmod error %s\n", fname2);
	// fname2 파일에 사용자의 읽기,쓰기, 그룹 사용자의 읽기, 다른 사용자의 읽기, 실행 권한 부여
	exit(0);
}
