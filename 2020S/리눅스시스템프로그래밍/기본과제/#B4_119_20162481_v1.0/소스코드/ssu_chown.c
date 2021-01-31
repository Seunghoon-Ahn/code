#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
	struct stat statbuf;
	char *fname = "ssu_myfile";
	int fd;

	if((fd = open(fname, O_RDWR | O_CREAT, 0600)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	} //파일을 읽기 쓰기 가능한 상태로 오픈함, 파일이 없을경우 새로 생성
	//파일 오픈이나 생성에 실패하였을 경우, 에러 메시지 출력 후 프로그램 종료

	close(fd); //파일을 닫음
	stat(fname, &statbuf); //stat() 함수를 이용해 파일의 정보를 statbuf에 저장함
	printf("# 1st stat call # UID:%d	GID:%d\n", statbuf.st_uid, statbuf.st_gid);
	//현재 파일의 User ID와 Group ID를 출력함
	if(chown(fname, 501, 300) < 0) {
		fprintf(stderr, "chown error for %s\n", fname);
		exit(1);
	}//chown() 함수를 이용해 파일의 UID와 GID를 각각 501, 300으로 변경함
	//실패시 오류 메시지 출력 후 프로그램 종료
	stat(fname, &statbuf); //파일의 정보를 statbuf에 저장함
	printf("# 2nd stat call # UID:%d	GID:%d\n", statbuf.st_uid, statbuf.st_gid);
	//변경 후의 파일의 User ID와 Group ID를 출력함
	if(unlink(fname) < 0) {
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	} //unlink() 함수를 통해서 파일의 링크를 해제함

	exit(0);
}
