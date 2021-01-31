#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	static struct {
		long offset;
		int length;
	} table [TABLE_SIZE];
	char buf[BUFFER_SIZE];
	long offset;
	int entry;
	int i;
	int length;
	int fd;

	if(argc < 2) {
		fprintf(stderr, "Usage : %s <file>\n", argv[0]);
		exit(1);
	} //인자를 적게 주었을 경우, 사용자에게 사용법을 출력하고 프로그램 종료

	if((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
			exit(1);
	} //파일을 읽기 전용으로 오픈, 실패시 에러메시지 출력

	entry = 0;
	offset = 0;
	
	while((length = read(fd, buf, BUFFER_SIZE)) > 0) {
		for(i = 0; i < length; i++) {
			table[entry].length++;
			offset++;

			if(buf[i] == '\n')
				table[++entry].offset = offset;
		}
	} //파일의 내용을 버퍼에 저장함
	// table 구조체를 이용하여 문자열의 길이를 저장하고, 오프셋의 위치를 저장함

#ifdef DEBUG
	for(i = 0; i < entry;i++)
		printf("%d : %ld, %d\n", i+1, table[i].offset, table[i].length);
#endif //디버깅 시에는 table을 출력하여 table의 작동 상태를 확인함

	while(1) {
		printf("Enter line number : ");
		scanf("%d", &length);
	//사용자로부터 출력을 원하는 라인 번호를 입력 받음
		if(--length < 0)
			break;
		//입력받은 라인 번호가 1보다 작을경우 무한루프 종료
		lseek(fd, table[length].offset, 0);
		//입력받은 라인 번호가 유의미할 경우 그 위치로 offset을 이동시킴
		if(read(fd, buf, table[length].length) <= 0)
			continue;
	//length만큼 파일에서 buf로 읽어옴
		buf[table[length].length] = '\0';
		//문자열로 만들기 위해 마지막에 null문자 삽입
		printf("%s", buf); //buf에 저장된 문장 출력
	}

	close(fd); //fd에 연결된 파일을 닫음
	exit(0);
}

