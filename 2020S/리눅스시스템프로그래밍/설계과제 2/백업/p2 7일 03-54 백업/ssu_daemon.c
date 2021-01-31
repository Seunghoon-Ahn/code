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
int dir_check(const struct dirent *info);

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
	//fprintf(logfp, "hit");


	while(1) {
		check_size = 0;
		//fprintf(logfp, "hit");
		dir_read2(tmppath); //비교를 위해 디렉토리를 읽어옴

		find_mc();
		find_delete();
		sleep(1);
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

	}
	return;
}

void find_mc(void)
{
	struct tm *t;
	char buf[512];

	//fprintf(logfp, "tlqkf22");
	//여기까지는 확인

	for(int i = 0; i < check_size; i++) {
		int cnt = 0;
		int tmp;
		//fprintf(logfp,"check_size = %d\n", check_size);
		for(int j = 0; j < fs_size; j++) {
			//fprintf(logfp, "i = %ld, j = %ld\n", checkarr[i].c_time, fsarr[j].c_time);
			if(!(tmp = strcmp(checkarr[i].fpath, fsarr[j].fpath))) {
				cnt= 1;
				//fprintf(logfp, "%ld %ld\n",checkarr[i].c_time, fsarr[j].c_time);
				if(checkarr[i].c_time != fsarr[j].c_time) {
					//fprintf(logfp, "%d %d\n%s\n%s\n",i, j, checkarr[i].fpath, fsarr[j].fpath);
					
					t = localtime(&checkarr[i].c_time);
					print_day(t, buf);
					fprintf(logfp, "%s", buf);
					fprintf(logfp, "[modify_");
					fprintf(logfp, "%s", strstr(checkarr[i].fpath, "check/")+6);
					fprintf(logfp, "]\n");
					//fprintf(logfp, "tlqkf");
					fsarr[j].c_time = checkarr[i].c_time;
					break;
				}
				else
					continue;
			}
		}
		if(!cnt) {
			strcpy(fsarr[fs_size].fpath, checkarr[i].fpath);
			fsarr[fs_size].c_time = checkarr[i].c_time;
			fs_size++;
			t = localtime(&checkarr[i].c_time);
			print_day(t, buf);
			fprintf(logfp, "%s", buf);
			fprintf(logfp, "[create_");
			fprintf(logfp, "%s", strstr(checkarr[i].fpath, "check/")+6);
			fprintf(logfp, "]\n");

		}

	}

	return;
}

void print_day(struct tm *t, char *buf)
{
	//char tmp[512] = {0, };
	sprintf(buf, "[%4d-%02d-%02d %02d:%02d:%02d]",
		1900+t->tm_year, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	//strcpy(buf, tmp);
	return;
}

int dir_check(const struct dirent *info) {
	if(!strncmp(info->d_name, ".", 1))
		return 0;
	else 
		return 1;
}




void dir_read2(char path[]) {
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
		//strcpy(fsarr[fs_size].fpath, namelist[i]->d_name);
		fsarr[fs_size].c_time = statbuf.st_mtime;
		fs_size++;
		if(S_ISDIR(statbuf.st_mode))
			dir_read(namelist[i]->d_name);
	}
	chdir("..");
	return;
}