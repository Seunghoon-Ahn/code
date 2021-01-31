#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RW_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
//RW_MODE로 0644 권한 지정
int main(void)
{
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";

	umask(0); //초기 umask는 0으로 지정
	
	if(creat(fname1, RW_MODE) < 0) {
		fprintf(stderr, "creat error for %s\n", fname1);
		exit(1);
	} //파일을 0644 권한으로 생성함, 실패시 오류메시지 출력 후 종료
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	//umask를 0044 권한을 삭제함
	if(creat(fname2, RW_MODE) < 0) {
		fprintf(stderr, "creat error for %s\n", fname2);
		exit(1);
	} //최종적으로 fname2 파일은 0600권한으로 생성됨

	exit(0);
} //프로세스에서 변경한 umask 값은 shell의 umask값에 변화를 주지 않음
