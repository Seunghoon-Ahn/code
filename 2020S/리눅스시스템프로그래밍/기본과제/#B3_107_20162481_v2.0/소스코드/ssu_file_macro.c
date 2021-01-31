#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat file_info;
	char *str;
	int i;

	for(i = 1; i <argc; i++) {
		printf("name = %s, type = ", argv[i]);
		//파일 이름 출력
		if(lstat(argv[i], &file_info) < 0) {
			fprintf(stderr, "lstat error\n");
			continue; //파일의 데이터를 lstat함수를 통해
		}          	//file_info구조체에 저장함

		if(S_ISREG(file_info.st_mode)) //일반 파일
			str = "regular";
		else if(S_ISDIR(file_info.st_mode)) //디렉터리 파일
			str = "directory"; 
		else if (S_ISCHR(file_info.st_mode))//문자 특수 파일
			str = "character special";
		else if (S_ISBLK(file_info.st_mode))//블록 특수 파일
			str = "block special";
		else if (S_ISFIFO(file_info.st_mode))//FIFO파일
			str = "FIFO";
		else if (S_ISLNK(file_info.st_mode))//심볼릭 링크 파일
			str = "symbolic link";
		else if (S_ISSOCK(file_info.st_mode))//소켓 파일
			str = "socket";
		else
			str = "unknown mode"; //알수 없는 파일
		//파일의 st_mode를 표준 매크로 들과 비교하여, 파일의 종류를 판단함
		//알 수 없는 파일의 경우 unknown을 출력함
		printf("%s\n", str); //파일의 종류 출력
	}
	exit(0);
}
