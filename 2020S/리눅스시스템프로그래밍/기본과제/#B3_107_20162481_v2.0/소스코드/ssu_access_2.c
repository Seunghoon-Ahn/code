#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TABLE_SIZE (sizeof(table)/sizeof(*table))

int main(int argc, char *argv[])
{
	struct {
		char *text;
		int mode;
	} table[] = {
		{"exists", 0}, //존재
		{"excute", 1}, //실행
		{"write", 2},  //쓰기
		{"read", 4}    //읽기
	};
	int i;

	if(argc < 2) {
		fprintf(stderr, "usage : %s <file>\n", argv[0]);
		exit(1);
	} //인자가 적게 입력되었을 경우 사용법 출력 후 프로그램 종료

	for(i = 0; i < TABLE_SIZE; i++) {
		if(access(argv[1], table[i].mode) != -1)
			printf("%s -ok\n", table[i].text);
		else
			printf("%s\n", table[i].text);
	}
	//access 함수를 통해 사용자가 파일에 접근 할 수 있는 권한을 판단함
	//table 구조체를 통해 파일의 존재, 실행, 쓰기, 읽기 가능 여부를 판단함
	exit(0);
}

