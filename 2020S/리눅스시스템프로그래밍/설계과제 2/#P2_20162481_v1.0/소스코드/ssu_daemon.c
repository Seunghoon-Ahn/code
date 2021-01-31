#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int mydaemon_init(void); //디몬프로세스를 생성하는 함수
void dir_read(char path[]); //초기에 디렉토리를 스캔하는 함수
void dir_read2(char path[]); //while문 내부에서 반복해서 디렉토리를 스캔하는 함수
void find_mc(void); //modify와 create를 탐색하는 함수
void find_delete(void); //delete를 탐색하는 함수
void print_day(struct tm *t, char buf[]); //날짜를 출력하기 위한 함수
int dir_check(const struct dirent *info); //scandir을 위한 필터함수

typedef struct File_Stat {
	char fpath[1024];
	time_t c_time;
} FS;

FS fsarr[1024]; //초기에 스캔한 것
FS checkarr[1024]; //반복해서 스캔해서 처음꺼랑 비교하기 위함
int fs_size = 0; //초기의 스캔한거 갯수
int check_size = 0; //나중에 스캔한거 갯수
FILE *logfp;


void make_daemon(void) {
	pid_t pid;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0)
		mydaemon_init();

	return;
}

int mydaemon_init(void) {
	pid_t pid;
	int fd, maxfd, fd2;
	char curpath[1024] = {0, };
	char tmppath[1024] = {0, };
	

	char buf[1024] = {0, };

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (pid != 0)
		exit(0); 
	
	setsid(); 
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	maxfd = getdtablesize();

	for(fd = 0; fd < maxfd; fd++)
		close(fd); 

	umask(0);

  getcwd(curpath, 1024); //현재 작업디렉토리 저장
  strcpy(tmppath, curpath); //임시로 현재 디렉토리 추가로 저장
  
  strcat(curpath, "/log.txt");
  strcat(tmppath, "/check");

  chdir("/");
  fd = open("/dev/null", O_RDWR);
  dup(0);
  dup(0); 

  if((logfp = fopen(curpath, "a+")) < 0) {
  	fprintf(stderr, "fopen error\n");
  	return 0;
  } //curpath는 ./log.txt의 절대경로
  setbuf(logfp, NULL); //버퍼를 없앰

  chdir(tmppath); // check 폴더로 이동

  dir_read(tmppath); //최초 디렉토리 스캔

  while(1) {
  	check_size = 0;
	dir_read2(tmppath); //비교를 위해 디렉토리를 읽어옴

	find_mc(); //modify create 확인
	find_delete(); //delete 확인
	sleep(1); //1초 멈춤
}

return 0;
}

void find_delete(void) {
	struct tm *t;
	time_t now;
	char buf[512];
	int idx = 0;

	for(int i = 0; i < fs_size; i++) {
		idx = 0;

		for(int j = 0; j < check_size; j++) {
			if(!(strcmp(fsarr[i].fpath, checkarr[j].fpath)))
		idx = 1; //이름이 일치하는 파일이 있는 경우 idx = 1
}
	if(idx == 0) { //이름이 일치하는 경우가 없는 경우
		now = time(NULL);
		t = localtime(&now);
		print_day(t, buf);
		fprintf(logfp, "%s", buf);
		fprintf(logfp, "[delete_");
		fprintf(logfp, "%s", strstr(fsarr[i].fpath, "check/")+6);
		fprintf(logfp, "]\n");

		fsarr[i] = fsarr[fs_size-1];
		strcpy(fsarr[fs_size - 1].fpath, "\0");
		fsarr[fs_size - 1].c_time = 0;
		fs_size--;
	}
  } //기존목록에는 있지만 새목록에는 없는 경우 삭제되었다고 판단함
  return;
}

void find_mc(void) //modify와 create를 판단하는 함수
{
	struct tm *t;
	time_t cur;
	char buf[512];

	for(int i = 0; i < check_size; i++) {
		int cnt = 0;
		for(int j = 0; j < fs_size; j++) {
			if(!strcmp(checkarr[i].fpath, fsarr[j].fpath)) {
				cnt= 1;
				if(checkarr[i].c_time != fsarr[j].c_time) {

					t = localtime(&checkarr[i].c_time);
					print_day(t, buf);
					fprintf(logfp, "%s", buf);
					fprintf(logfp, "[modify_");
					fprintf(logfp, "%s", strstr(checkarr[i].fpath, "check/")+6);
					fprintf(logfp, "]\n");
					fsarr[j].c_time = checkarr[i].c_time;
					break;
				}
				else
					continue;
	  } //둘을 비교했을때 이름이 같고, 시간이 다르면 modify, 구 목록 업데이트 해줌
	}
	if(!cnt) {
		strcpy(fsarr[fs_size].fpath, checkarr[i].fpath);
		fsarr[fs_size].c_time = checkarr[i].c_time;
		fs_size++;
		cur = time(NULL);
		t = localtime(&cur);
		print_day(t, buf);
		fprintf(logfp, "%s", buf);
		fprintf(logfp, "[create_");
		fprintf(logfp, "%s", strstr(checkarr[i].fpath, "check/")+6);
		fprintf(logfp, "]\n");
	} //이름이 같은 적이 한번도 없었다면 새로 생긴 파일로 판단함
}

return;
}

void print_day(struct tm *t, char *buf)
{
	sprintf(buf, "[%4d-%02d-%02d %02d:%02d:%02d]",
		1900+t->tm_year, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	return;
}

int dir_check(const struct dirent *info) {
	if(!strncmp(info->d_name, ".", 1))
		return 0;
	else 
		return 1;
}

void dir_read2(char path[]) { //새 목록을 생성하는 함수
	struct dirent **namelist;
	int count;
	char buf[1024] = {"./"};
	char buf2[1024];
	char *ptr;

	memset(buf2, 0, sizeof(buf2));

	if((count = scandir(path, &namelist, dir_check, alphasort)) == -1) {
		return;
	}
	chdir(path);
	for(int i = 0; i < count; i++) {
		struct stat statbuf;
		strcpy(buf, "./");

		memset(buf2, 0, sizeof(buf2));

		if(!(strcmp(namelist[i]->d_name, ".")) || !(strcmp(namelist[i]->d_name, "..")))
			continue;
		stat(namelist[i]->d_name, &statbuf);

		realpath(namelist[i]->d_name, buf2);
		ptr = strstr(buf2, "check");
		strcat(buf, ptr);
		strcpy(checkarr[check_size].fpath, buf);
		checkarr[check_size].c_time = statbuf.st_mtime;
		check_size++;
		if(S_ISDIR(statbuf.st_mode))
			dir_read2(namelist[i]->d_name);
  } //파일의 경로를 절대경로로 만들어 준 후, check 이후면 저장해서 상대경로로 구조체에 저장
  chdir("..");
  return;
}

void dir_read(char path[]) { // 초기 파일 목록을 생성하는 함수
	struct dirent **namelist;
	int count;
	char buf[1024] = {"./\0"};
	char buf2[1024];
	char *ptr;

	memset(buf2, 0, sizeof(buf2));

	if((count = scandir(path, &namelist, dir_check, alphasort)) == -1) {
		return;
	}
	chdir(path);
	for(int i = 0; i < count; i++) {
		struct stat statbuf;
		strcpy(buf, "./\0");

		memset(buf2, 0, sizeof(buf2));

		if(!(strcmp(namelist[i]->d_name, ".")) || !(strcmp(namelist[i]->d_name, "..")))
			continue;
		stat(namelist[i]->d_name, &statbuf);

		realpath(namelist[i]->d_name, buf2);
		ptr = strstr(buf2, "check");
		strcat(buf, ptr);
		strcpy(fsarr[fs_size].fpath, buf);
		fsarr[fs_size].c_time = statbuf.st_mtime;
		fs_size++;
		if(S_ISDIR(statbuf.st_mode))
			dir_read(namelist[i]->d_name);
  } //파일의 경로를 절대경로로 만들어 준 후, check 이후면 저장해서 상대경로로 구조체에 저장
  chdir("..");
  return;
}