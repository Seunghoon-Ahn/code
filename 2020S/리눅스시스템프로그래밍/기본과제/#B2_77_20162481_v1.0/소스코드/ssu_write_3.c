#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char *argv[])
{
	struct ssu_employee record;
	int fd;
	if(argc < 2) {
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}
	//인자가 적게 입력되었을 경우, 사용자에게 사용법을 알려준 후 프로그램 종료
	if((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}
	//인자로 입력받은 파일을 오픈, 파일이 없는경우 새로 생성함
	//권한은 0640 부여함, 실패 시 오류 메시지 출력 후 프로그램 종료
	while(1) { //name으로 . 이 입력될떄 까지 반복해서 입력 받음
		printf("Enter employee name <SPACE> salary : ");
		scanf("%s", record.name);
		
		if(record.name[0] == '.')
			break;

		scanf("%d", &record.salary);
		record.pid = getpid();
		write(fd, (char *)&record, sizeof(record));
	} //입력 받은 이름과 월급 정보를 파일에 write함
	close(fd); //파일을 닫음
	exit(0);
}

