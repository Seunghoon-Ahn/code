#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define NAMESIZE 50

struct employee{
	char name[NAMESIZE];
	int salary;
	int pid;
};

int main(int argc, char *argv[]) {
	struct flock lock;
	struct employee record;
	int fd, recnum, pid;
	long position;
	char ans[5];

	if((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(1);
	} //파일을 오픈함

	pid = getpid(); //프로세스 ID를 가져옴

	for(;;) {
		printf("\nEnter record number: ");
		scanf("%d", &recnum);
		if(recnum < 0)
			break;

		position = recnum * sizeof(record);
		lock.l_type = F_RDLCK; // 읽기 잠금 설정
		lock.l_whence = 0;
		lock.l_start = position;
		lock.l_len = sizeof(record);
		 //lock 구조체 변수 설정
		if(fcntl(fd, F_SETLKW, &lock) == -1) {
			perror(argv[1]);
			exit(2);
		} //lock 설정을 fd가 가리키는 파일에 설정
		lseek(fd, position, 0); //position의 위치로 이동
		if(read(fd, (char *)&record, sizeof(record)) == 0) {
			printf("record %d not fund\n", recnum);
			lock.l_type = F_UNLCK;
			fcntl(fd, F_SETLK, &lock);
			continue;
		} //파일을 읽었을때 없는경우 예외처리
		printf("Employee: %s, salary: %d\n", record.name, record.salary);
		printf("Do you want to update salary (y or n)? ");
		scanf("%s", ans);

		if(ans[0] != 'y') {
			lock.l_type = F_UNLCK; //잠금 해제
			fcntl(fd, F_SETLK, &lock); //잠금 해제를 fd에 적용
			continue;
		} 
		lock.l_type = F_WRLCK; //쓰기 잠금 설정
		if(fcntl(fd, F_SETLKW, &lock) == -1) { //설정 반영
			perror(argv[1]);
			exit(3);
		}
		record.pid = pid;
		printf("Enter new salary: ");
		scanf("%d", &record.salary);

		lseek(fd, position, 0);
		write(fd, (char *)&record, sizeof(record));
		//새 salary를 입력받은 경우 파일에 써줌
		lock.l_type = F_UNLCK; //잠금해제
		fcntl(fd, F_SETLK, &lock); //잠금 해제 반영
	}
	close(fd); //파일을 닫음
}
