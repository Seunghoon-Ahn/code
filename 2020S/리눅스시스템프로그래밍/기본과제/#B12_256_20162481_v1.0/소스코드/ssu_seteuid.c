#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
	int fd, state;
	state = seteuid(1000); //seteuid를 통해 유효사용자 ID를 1000으로 바꿈
	//seteuid의 결과를 state 변수에 저장
	if(state < 0) {
		fprintf(stderr, "seteuid error\n");
		exit(1);
	} //seteuid가 실패하였을 경우 에러 출력 후 프로그램 종료

	if((fd = open("ssu_test.txt", O_CREAT | O_RDWR, S_IRWXU)) < 0) {
		fprintf(stderr, "open error\n");
		exit(1);
	}// ssu_test.txt 파일을 읽기쓰기 모드로 오픈함, 파일이 없는 경우 새로 생성
	//파일 소유자에게 읽기 쓰기 실행 권한을 부여
	close(fd); //파일을 닫음
	exit(0); //프로그램 종료
}
