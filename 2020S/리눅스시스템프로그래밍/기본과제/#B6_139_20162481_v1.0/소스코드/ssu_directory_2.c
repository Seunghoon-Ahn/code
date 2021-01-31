#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax=0;
#endif

#define MAX_PATH_GUESSED 1024

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

char *pathname;
char command[LINE_MAX], grep_cmd[LINE_MAX];

int ssu_do_grep(void) {
	struct dirent *dirp;
	struct stat statbuf;
	char *ptr;
	DIR *dp;

	if(lstat(pathname, &statbuf) < 0) {
		fprintf(stderr, "lstat error for %s\n", pathname);
		return 0;
	} //lstat() 함수로 파일의 정보를 불러와 statbuf에 저장함
	//실패시 오류메시지 출력 후 프로그램 종료
	if(S_ISDIR(statbuf.st_mode) == 0) {
		sprintf(command, "%s %s", grep_cmd, pathname);
		printf("%s : \n", pathname);
		system(command);
		return 0;
	} //파일이 디렉터리 파일인지 확인한 후, 디렉터리 파일일 경우
	//pathname의 파일에 대해 grep명령어를 실행함

	ptr = pathname + strlen(pathname);
	*ptr++ = '/';
	*ptr = '\0';

	if((dp = opendir(pathname)) == NULL) {
		fprintf(stderr, "opendir error for %s\n", pathname);
		return 0;
	}

	while((dirp = readdir(dp)) != NULL)
		if(strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")) {
			strcpy(ptr, dirp->d_name);

			if(ssu_do_grep() < 0)
				break;
		}

	ptr[-1] = 0;
	closedir(dp);
	return 0;
}

void ssu_make_grep(int argc, char *argv[]) {
	int i;
	strcpy(grep_cmd, " grep");
	//command로 입력할 명령어 가장 앞에 grep추가
	for(i = 1; i < argc-1; i++) {
		strcat(grep_cmd, " ");
		strcat(grep_cmd, argv[i]);
	} //command로 입력할 명령어에 각종 옵션들을 추가
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "usage: %s <-CVbchilnsvwx> <-num> <-A num> <-B num> <-f file> \n"
				"		<-e> expr <directory>\n", argv[0]);
		exit(1);
	} //인자가 적게 들어왔을 경우 사용법을 출력하고 프로그램 종료

	if(pathmax == 0) {
		if((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
			pathmax = MAX_PATH_GUESSED;
		else
			pathmax++;
	}

	if((pathname = (char *) malloc(pathmax+1)) == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	} //경로의 길이만큼 동적할당함

	strcpy(pathname, argv[argc-1]); //인자로 입력받은 경로를 pathname에 복사
	ssu_make_grep(argc, argv);
	ssu_do_grep();
	exit(0);
}
