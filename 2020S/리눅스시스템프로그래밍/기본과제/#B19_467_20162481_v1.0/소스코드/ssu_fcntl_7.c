#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	char *filename = "ssu_test.txt";
	int fd1, fd2;
	int flag;

	if((fd1 = open(filename, O_RDWR | O_APPEND, 0644)) < 0) {
		fprintf(stderr, "open error for %s\n", filename);
		exit(1);
	} // 파일을 읽기 쓰기 모드로 오픈, 파일 디스크립터는 fd1에 저장

	if(fcntl(fd1, F_SETFD, FD_CLOEXEC) == -1) {
		fprintf(stderr, "fcntl F_SETFD error\n");
		exit(1);
	} //fd1에 CLOEXEC 플래그 설정

	if((flag = fcntl(fd1, F_GETFL, 0)) == -1) {
		fprintf(stderr, "fcntl F_GETFL error\n");
		exit(1);
	} //fd1의 플래그 설정을 flag에 저장

	if(flag & O_APPEND) //flag에 O_APPEND 포함 여부 확인
		printf("fd1 : O_APPEND flag is set.\n");
	else
		printf("fd1 : O_APPEND flag is NOT set.\n");

	if((flag = fcntl(fd1, F_SETFD, 0)) == -1) {
		fprintf(stderr, "fcntl F_GETFD error\n");
		exit(1);
	} //fd1의 플래그 인자를 재설정

	if(flag & FD_CLOEXEC) //CLOEXEC의 포함 여부 확인
		printf("fd1 : FD_CLOEXEC flag is set.\n");
	else
		printf("fd1 : FD_CLOEXEC flag is NOT set.\n");
	
	if((fd2 = fcntl(fd1, F_DUPFD, 0)) == -1) {
		fprintf(stderr, "fcntl F_DUPFD error\n");
		exit(1);
	}//fd1의 파일 디스크립터를 0으로 복사
	//0번은 사용중이므로 가능한것중 가장 큰 것 부여

	if((flag = fcntl(fd2, F_GETFL, 0)) == -1) {
		fprintf(stderr, "fcntl F_GETFL error\n");
		exit(1);
	} //fd2의 플래그를 flag에 저장
	
	if(flag & O_APPEND) //O_APPEND 포함 여부 확인
		printf("fd2 : O_APPEND flag is set.\n");
	else
		printf("fd2 : O_APPEND flag is NOT set.\n");

	if((flag = fcntl(fd2, F_GETFD, 0)) == -1) {
		fprintf(stderr, "fcntl F_GETFD error\n");
		exit(1);
	} //fd2의 플래그를 flag에 저장

	if(flag &FD_CLOEXEC) // CLOEXEC 포함 여부 확인
		printf("fd2 : FD_CLOEXEC flag is set.\n");
	else
		printf("fd2 : FD_CLOEXEC flag is NOT set.\n");

	exit(0);
}
