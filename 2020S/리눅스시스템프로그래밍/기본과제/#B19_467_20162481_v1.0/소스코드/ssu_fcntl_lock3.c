#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>

#define NAMESIZE 50

struct employee{
	char name[NAMESIZE];
	int salary;
	int pid;
};

int main(int argc, char *argv[])
{
	struct flock lock;
	struct employee record;
	int fd, recnum, pid;
	long position;

	if((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(1);
 	} //파일을 오픈함
	
	pid = getpid(); //프로세스 ID를 불러옴
	for(;;) {
		printf("\nEnter record number: ");
		scanf("%d", &recnum);
		if(recnum < 0)
			break; //음수 입력시 종료
		position = recnum * sizeof(record);
		lock.l_type = F_WRLCK; //쓰기 잠금 설정
		lock.l_whence = 0;
		lock.l_start = position;
		lock.l_len = sizeof(record);
		//flock 설정
		if(fcntl(fd, F_SETLKW, &lock) == -1) {
			perror(argv[1]);
			exit(2);
		} //fd에 lock을 적용함
		lseek(fd, position, 0);
		if(read(fd, (char *)&record, sizeof(record)) == 0) {
			printf("record %d not foound\n", recnum);
			lock.l_type = F_UNLCK; //파일 잠금 해제
			fcntl(fd, F_SETLK, &lock); //fd에 lock을 적용함
			continue;
		} //파일을 읽어옴
		printf("Employee: %s, salary: %d\n", record.name, record.salary);
		record.pid = pid;
		printf("Enter new salary: ");
		scanf("%d", &record.salary);
		lseek(fd, position, 0);
		write(fd, (char *)&record, sizeof(record));
		//파일에 새 정보를 씀
		lock.l_type = F_UNLCK; //파일 잠금 해제
		fcntl(fd, F_SETLK, &lock); //파일에 lock를 적용함
	}
	close(fd);
}

