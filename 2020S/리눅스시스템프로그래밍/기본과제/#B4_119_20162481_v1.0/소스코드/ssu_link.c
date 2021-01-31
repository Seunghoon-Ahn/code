#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 3) {
		fprintf(stderr, "usage : %s <file1> <file2>\n", argv[0]);
		exit(1);
	} //인자가 적게 들어왔을 경우 사용법을 출력한 후 프로그램 종료
	
	if(link(argv[1], argv[2]) == -1) {
		fprintf(stderr, "link error for %s\n", argv[1]);
		exit(1);
	} //첫번째 파일과 두번째 파일을 링크시킴
	//링크에 실패하였을 경우 에러 메시지 출력 후 프로그램 종료
	exit(0);
}
