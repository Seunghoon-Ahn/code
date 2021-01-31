#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	int testfd;
	int fd;

	fd = open("test.txt", O_CREAT);

	testfd = fcntl(fd, F_DUPFD, 5); //fd의 파일 디스크립터를 5로 설정
	printf("testfd :%d\n", testfd); //출력
	testfd = fcntl(fd, F_DUPFD, 5); //fd의 파일 디스크립터를 5로 설정
	printf("testfd :%d\n", testfd); //출력
	//2번째로 5로 파일 디스크립터를 지정할때, 5는 이미 사용중이므로
	//5보다 큰 값중에 가장 작은 값인 6으로 지정됨
	getchar();
}
