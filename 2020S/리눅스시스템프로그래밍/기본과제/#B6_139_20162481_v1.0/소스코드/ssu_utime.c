#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[])
{
	struct utimbuf time_buf;
	struct stat statbuf;
	int fd;
	int i;

	for(i = 1; i < argc; i++){
		if(stat(argv[i], &statbuf) < 0) {
			fprintf(stderr, "stat error for %s\n", argv[i]);
			continue;
		} //stat() 함수로 파일의 최종접근시간과 최종 수정시간을 저장함

		if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
			fprintf(stderr, "open error for %s\n", argv[i]);
			continue;
		}
		//파일을 오픈하여 최종 접근 시간을 수정함
		close(fd);
		time_buf.actime = statbuf.st_atime; //actime에 오픈 전 최종 접근시각을 저장
		time_buf.modtime = statbuf.st_mtime; //modtime에 오픈전 최종 수정시간을 저장

		if(utime(argv[i], &time_buf) < 0) {
			fprintf(stderr, "utime error for %s\n", argv[i]);
			continue;
		} //utime()함수를 이용하여 파일을 오픈 하기 전의 시간을 파일에 덮어씌움
	}
	exit(0); //프로그램 종료
}
