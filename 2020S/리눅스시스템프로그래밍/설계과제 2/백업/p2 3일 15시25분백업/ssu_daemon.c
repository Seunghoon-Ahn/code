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

extern int daemon_pid;
int mydaemon_init(void);
void dir_read(char path[]);
void dir_read2(char path[]);
void find_mc(void);
void find_delete(void);
void print_day(struct tm *t, char buf[]);

typedef struct File_Stat {
	char fpath[1024];
	time_t c_time;
} FS;

FS fsarr[1024]; //초기에 스캔한 것
FS checkarr[1024]; //반복해서 스캔해서 처음꺼랑 비교하기 위함
int fs_size = 0; //초기의 스캔한거 갯수
int check_size = 0; //나중에 스캔한거 갯수
FILE *logfp;
struct tm *t;

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
	// 디렉토리의 파일들을 저장하기 위한 무언가가 필요해

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (pid != 0)
		exit(0); 
	
	daemon_pid = pid = getpid(); 

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
	// 여기부터 디몬 프로세스가 할 일 만들기

	if((logfp = fopen(curpath, "a+")) < 0) {
		fprintf(stderr, "fopen error\n");
		return 0;
	} //curpath는 ./log.txt의 절대경로
	setbuf(logfp, NULL); //버퍼를 없앰

	chdir(tmppath); // check 폴더로 이동
					//필요한가??????


	dir_read(tmppath);

/*
	for(int i = 0; i < fs_size; i++) {
		fprintf(logfp, "%s\n", fsarr[i].fpath);
		fprintf(logfp, "%ld\n", fsarr[i].c_time);
	}
	 //초기에 전체 파일 목록 불러옴
	//fs_size에 현재 파일 갯수 저장되어있음
*/

/*
FS fsarr[1024]; //초기에 스캔한 것
FS checkarr[1024]; //반복해서 스캔해서 처음꺼랑 비교하기 위함
int fs_size = 0; //초기의 스캔한거 갯수
int check_size = 0; //나중에 스캔한거 갯수

typedef struct File_Stat {
	char fpath[1024];
	time_t c_time;
} FS;
*/
	while(1) {
		dir_read2(tmppath); //비교를 위해 디렉토리를 읽어옴

		find_mc();
		find_delete();
	}

	return 0;
}

void find_mc(void)
{
	char buf[512];

	for(int i = 0; i < check_size; i++) {
		int cnt = 0;
		for(int j = 0; i < fs_size; j++) {
			if(!strcmp(checkarr[i].fpath, fsarr[j].fpath)) {
				if(checkarr[i].c_time != fsarr[i].c_time) {
					t = localtime(checkarr[i].c_time);
					print_day(t, buf);
					fprintf(logfp, buf);
				}
			}





		}

	}


}

void print_day(struct tm *t, char *buf)
{
	char tmp[512] = {0, };
	sprintf(tmp, "[%4d-%02d-%02d %02d:%02d:%02d]",
		1900+t->tm_year, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	strcpy(buf, tmp);
	return;
}




void find_delete(void) {





}



void dir_read2(char path[]) {
	struct dirent **namelist;
	int count;
	char buf[1024] = {"./\0"};
	char buf2[1024];
	char *ptr;

	memset(buf2, 0, sizeof(buf2));

	if((count = scandir(path, &namelist, NULL, alphasort)) == -1) {
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
		strcpy(checkarr[check_size].fpath, buf);
		checkarr[check_size].c_time = statbuf.st_mtime;
		fs_size++;
		if(S_ISDIR(statbuf.st_mode))
			dir_read2(namelist[i]->d_name);
	}
	chdir("..");
	return;
}












void dir_read(char path[]) {
	struct dirent **namelist;
	int count;
	char buf[1024] = {"./\0"};
	char buf2[1024];
	char *ptr;

	memset(buf2, 0, sizeof(buf2));

	if((count = scandir(path, &namelist, NULL, alphasort)) == -1) {
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
		//strcpy(fsarr[fs_size].fpath, namelist[i]->d_name);
		fsarr[fs_size].c_time = statbuf.st_mtime;
		fs_size++;
		if(S_ISDIR(statbuf.st_mode))
			dir_read(namelist[i]->d_name);
	}
	chdir("..");
	return;
}