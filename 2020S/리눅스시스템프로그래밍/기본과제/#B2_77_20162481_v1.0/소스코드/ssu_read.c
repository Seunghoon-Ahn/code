#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char *argv[])
{
	struct ssu_employee record;
	int fd;
	int record_num;
	
	if(argc < 2) {
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	} //인자가 적게 들어올 경우 사용자에게 사용방법을 표시하고 프로그램 종료
	
	if((fd = open(argv[1], O_RDONLY)) < 0 ) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	} // 인자로 입력받은 파일을 오픈함. 실패할 경우 에러 메시지를 출력한 후 프로그램 종료

	while(1) { //record number로 음수가 들어올때 까지 반복하여 입력을 받음
		printf("Enter record number : ");
		scanf("%d", &record_num);

		if(record_num < 0)
			break; //음수가 입력될 경우 프로그램 종료

		if(lseek(fd, (long)record_num * sizeof(record), 0) < 0) {
			fprintf(stderr, "lseek error\n");
			exit(1); //record number의 위치만큼 offset을 이동시킴
		}

		if(read(fd, (char *)&record, sizeof(record)) > 0) //offset이 위치한 곳 부터 read 수행
			printf("Employee : %s Salary : %d\n", record.name, record.salary);
		else
			printf("Record %d not found\n", record_num);//데이터가 없는경우 사용자에게 알림
	}

	close(fd); //파일을 닫고 파일 디스크립터를 반환함
	exit(0); //프로그램 종료
}
