#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {
		fprintf(stderr, "usage : %s <filename> <newname>\n", argv[0]);
		exit(1);
	} //인자가 적게 들어왔을 경우 사용법 출력 후, 프로그램 종료

	if(link(argv[1], argv[2]) < 0) {
		fprintf(stderr, "Link error\n");
		exit(1);
	} // link() 함수를 통해 새로운 파일을 생성하여 원래 파일을 가리키게 함
	// 실패시 에러 메시지 출력 후 프로그램 종료
	else //성공시 step1 passed 출력
		printf("step1 passed.\n");

	if(remove(argv[1]) < 0) {
		fprintf(stderr, "remove error\n");
		remove(argv[2]);
		exit(1);
	} //remove() 함수를 이용해 원래의 파일을 삭제 함
	//실패시 에러 메시지 출력 후 프로그램 종료
	else //성공시 step2 passed 출력
		printf("step2 passed.\n");

	printf("Success!\n"); //최종적으로 success 출력
	exit(0); //프로그램 종료
}

