#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

#define DUMMY 0

int main(int argc, char *argv[]) {
	struct ssu_employee record;
	int fd;
	int flags;
	int length;
	int pid;

	if(argc <2) {
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	} //인자가 적은경우 에러처리

	if((fd = open(argv[1], O_RDWR)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	} //파일을 읽기쓰기 모드로 오픈함
	
	if((flags = fcntl(fd, F_GETFL, DUMMY)) == -1) {
		fprintf(stderr, "fcntl F_GETFL error\n");
		exit(1);
	} //fd의 플래그를 읽어와 flags 변수에 저장

	flags |= O_APPEND; //flags 에 O_APPEND 추가
	
	if(fcntl(fd, F_SETFL, flags) == -1) {
		fprintf(stderr, "fcntl F_SETFL error\n");
		exit(1);
	} //fd 의 플래그를 flags로 설정함
	pid = getpid(); //프로세스 아이디 얻어옴

	while(1) {
		printf("Enter employee name : ");
		scanf("%s", record.name);

		if(record.name[0] == '.')
			break;

		printf("Enter employee salary : ");
		scanf("%d", &record.salary);
		record.pid = pid;
		length = sizeof(record);
		//이름과 월급을 입력받음
		if(write(fd, (char *)&record, length) != length) {
			fprintf(stderr, "record write error\n");
			exit(1);
		} //입력받은 것을 파일에 씀
	}

	close(fd); //파일 디스크립터를 닫음
	exit(0);
}
