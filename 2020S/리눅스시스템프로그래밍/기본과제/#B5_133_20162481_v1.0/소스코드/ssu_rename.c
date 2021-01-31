#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;

	if(argc != 3) {
		fprintf(stderr, "usage : %s <oldname> <newname>\n", argv[0]);
		exit(1);
	} // 인자가 적게 들어왔을 경우 사용법 출력 후 프로그램 종료

	if((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "first open error for %s\n", argv[1]);
		exit(1);
	} //첫번째 파일을 불러옴, 실패 시 오류 메시지 출력 후 프로그램 종료
	else //파일을 불러오는 데에 성공 했으면 파일을 닫음
		close(fd);

	if(rename(argv[1], argv[2]) < 0) {
		fprintf(stderr, "rename error\n");
		exit(1);
	} //파일의 이름을 2번째로 입력한 이름으로 변경함
	// 실패시 오류 메시지 출력 후 프로그램 종료
	if((fd = open(argv[1], O_RDONLY)) < 0) 
		printf("second open error for %s\n", argv[1]);
	else { //첫번째 파일의 이름으로 파일 오픈 수행 -> 실패함
		fprintf(stderr, "it's very strange!\n");
		exit(1);
	} //만약 파일이 오픈 될 시에 오류 메시치 출력 후 프로그램 종료

	if((fd = open(argv[2], O_RDONLY)) < 0) {
		fprintf(stderr, "third open error for %s\n", argv[2]);
		exit(1);
	} // 2번째 파일의 이름으로 파일을 오픈, 실패 시 오류 출력 후 프로그램 종료

	printf("Everything is good!\n"); //프로그램의 끝까지 도달할 경우 출력
	exit(0); //프로그램 종료
}
