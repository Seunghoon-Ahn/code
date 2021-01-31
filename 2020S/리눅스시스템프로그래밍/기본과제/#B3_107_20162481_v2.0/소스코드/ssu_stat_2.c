#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

struct stat statbuf;

void ssu_checkfile(char *fname, time_t *time);

int main(int argc, char *argv[]) {
	time_t intertime;

	if(argc != 2) {
		fprintf(stderr, "usage : %s <file>\n", argv[0]);
		exit(1);
	} //인자가 적게 입력되었을 경우 사용법을 출력하고 프로그램 종료

	if(stat(argv[1], &statbuf) < 0) {
		fprintf(stderr, "stat error for %s\n", argv[1]);
		exit(1);
	} //stat() 함수를 이용해 파일의 정보를 읽어와 statbuf에 저장함
	//실패시 오류메시지 출력후 프로그램 종료
	intertime = statbuf.st_mtime; //현재 파일의 최종 수정시간을 저장함
	while(1) {
		ssu_checkfile(argv[1], &intertime); //파일의 수정을 확인하는 함수 호출
		sleep(10); //10초 대기
	}
}

void ssu_checkfile(char *fname, time_t *time) {
	if(stat(fname, &statbuf) < 0) {
		fprintf(stderr, "Warning : ssu_checkfile() error!\n");
		exit(1);
	} // 파일이 없을경우 정보를 읽어오지 못함, 오류 메시지 출력 후 프로그램 종료
	else
		if(statbuf.st_mtime != *time) {
			printf("Warning : %s was modified!.\n", fname);
			*time = statbuf.st_mtime;
		} //파일이 수정되면 메시지를 출력하고, 최근 수정 시간을 새로 저장함
}

