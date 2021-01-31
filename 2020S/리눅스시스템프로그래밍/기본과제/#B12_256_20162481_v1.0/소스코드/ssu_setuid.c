#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char line[256];
	FILE *fp;
	int uid;

	if(argc <2) {
		fprintf(stderr, "usage: %s file_name\n", argv[0]);
		exit(1);
	} //인자가 적게 입력되었을 경우, 사용법을 출력하고 프로그램 종료

	printf("initially uid = %d and euid = %d\n", getuid(), geteuid());
	// 초기 유저id와 유효 유저ID 출력
	fp = fopen(argv[1], "r");
	// 파일을 읽기 모드로 오픈함
	if(fp == NULL) {
		fprintf(stderr, "first open error for %s\n", argv[1]);
		exit(1);
	} //파일 오픈 실패시 에러 출력 후 프로그램 종료
	else {
		printf("first open successful:\n");
		// 파일 오픈에 성공함
		while(fgets(line, 255, fp) != NULL)
			fputs(line, stdout); // 파일의 끝에 닿을때까지 한줄씩 읽어와 출력함
		fclose(fp); //파일 닫음
	}

	setuid(uid = getuid()); // 현재의 유저 ID로 UID, EUID를 설정함
	printf("after setuid(%d):\n uid=%d and euid=%d\n", uid, getuid(), geteuid());
	//설정한 ID들을 출력하여 확인
	fp = fopen(argv[1], "r"); //파일을 오픈함
	
	if(fp == NULL) {
		fprintf(stderr, "second open error for %s\n", argv[1]);
		exit(1);
	} //파일 오픈에 실패한경우 오류 출력후 프로그램 종료
	else {
		printf("second open successful:\n");
		//파일 오픈 성공 시
		while(fgets(line, 255, fp) != NULL)
			fputs(line, stdout);
		//파일의 내용을 읽어옴
		fclose(fp); //파일을 닫음
	}
	exit(0); //프로그램 종료
}
