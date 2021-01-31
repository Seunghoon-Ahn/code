#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	if(chdir("/etc") < 0) {
		fprintf(stderr, "chdir error\n");
		exit(1);
	} //현재 작업 디렉터리를 /etc로 변경함, 실패시 에러메시지 출력 후 종료
	printf("chdir to /etc succeeded.\n");//변경 성공시 메시지 출력
	exit(0); //프로그램 종료
}
