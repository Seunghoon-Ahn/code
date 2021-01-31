#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <errno.h>

#define NAMESIZE 50
#define MAXTRIES 5

struct employee{
	char name[NAMESIZE];
	int salary;
	int pid;
};

int main(int argc, char *argv[])
{
	struct flock lock;
	struct employee record;
	int fd, sum = 0, try = 0;

	sleep(10);
	if((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(1);
 	} //파일을 오픈함

	lock.l_type = F_RDLCK; //읽기 잠금 설정
	lock.l_whence = 0;
	lock.l_start = 0L;
	lock.l_len = 0L;

	while(fcntl(fd, F_SETLK, &lock) == -1) {
		if(errno == EACCES) {
			if(try++ < MAXTRIES) {
				sleep(1);
				continue;
			}
			printf("%s busy -- try later\n", argv[1]);
			exit(2);
		}
		perror(argv[1]);
		exit(3);
	} //fd에 lock을 설정함
	sum = 0;
	while(read(fd, (char *)&record, sizeof(record)) > 0) {
		printf("Employee: %s, Salary: %d\n", record.name, record.salary);
		sum += record.salary;
	} //파일을 읽어서 출력함
	printf("\nTotal salary: %d\n", sum);

	lock.l_type = F_UNLCK; //잠금 해제
	fcntl(fd, F_SETLK, &lock); //lock을 파일 fd에 적용함
	close(fd); //파일 닫음
}

