#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char buf[64];
	char *fname = "ssu_tempfile";
	int fd;
	int length;

	if((fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0600)) < 0)
	{
		fprintf(stderr, "first open error for %s\n", fname);
		exit(1);
	} //파일을 읽기쓰기 가능한 상태로 오픈함, 파일이 없을경우 새로 생성함
	// 파일이 이미 존재할경우 파일을 초기화함, 오픈 실패시 에러 메시지 출력 후 종료

	if(unlink(fname) < 0) {
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	}//fname을 unlink시킴, 실패시 에러 메시지 출력 후 프로그램 종료

	if(write(fd, "How are you?", 12) != 12) {
		fprintf(stderr, "write error\n");
		exit(1);
	} //fd가 기리키는 파일에 문자열을 씀, 쓰기에 실패할 경우 에러 메시지 출력후 종료

	lseek(fd, 0, 0); //파일의 가장 처음으로 offset을 이동함

	if((length = read(fd, buf, sizeof(buf))) < 0) {
		fprintf(stderr, "buf read error\n");
		exit(1);
	} //read를 수행하고, 읽은 바이트만큼 length에 저장함, 실패시 에러 출력 후 종료
	else
		buf[length] = 0; //read를 수행하였으면, 문자열의 마지막에 널문자 입력

	printf("%s\n", buf); //문자열 출력
	close(fd); //파일을 닫음
	
	if((fd = open(fname, O_RDWR)) < 0) {
		fprintf(stderr, "second open error for %s\n", fname);
		exit(1);
	}//앞에서 unlink한 파일을 close했기 때문에 더이상 파일에 접근할 수 없음
	else
		close(fd);
	//따라서 파일 오픈에 실패하고 에러 메시지 출력 후 프로그램이 종료됨
	exit(0);
}

