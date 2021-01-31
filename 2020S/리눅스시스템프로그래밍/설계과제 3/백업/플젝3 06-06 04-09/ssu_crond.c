#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <syslog.h>
#include <signal.h>
#include <limits.h>
#include <utime.h>
#include <stdbool.h>

#define BUFSIZE 1024

int mydaemon_init(void);
void do_command(void);
void play_command(char buf[]);
void check_cycle(char arr[], int num);
int check_star(char arr[]);


FILE *filefp;
FILE *logfp;
char s_min[20];
char s_hour[20];
char s_day[20];
char s_month[20];
char s_wday[20];
//주기 받아옴
bool min[60];
bool hour[24];
bool day[32];
bool month[13];
bool wday[7];
//주기를 각각의 단위로 환산함

int main(void) {
	/*
	if(mydaemon_init() < 0) {
		fprintf(stderr, "daemon failed\n");
		exit(1);
	}

	return 0;
}

int mydaemon_init(void) {
	pid_t pid;
	int fd, maxfd;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid != 0)
		exit(0);

	pid = getpid();
	setsid(); 
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	maxfd = getdtablesize();

	for(fd = 0; fd < maxfd; fd++)
		close(fd); 

	umask(0);
	//chdir("/");
	fd = open("/dev/null", O_RDWR);
	dup(0);
	dup(0); 

*/
	//여기부터 디몬이 할일 짜기

	//시간을 읽어서 초가 00이면 시작

	if((filefp = fopen("ssu_crontab_file", "r")) == NULL) {
		fprintf(stderr, "fopen error for command file\n");
		exit(1);
	}

	if((logfp = fopen("ssu_crontab_log", "a+")) == NULL) {
		fprintf(stderr, "fopen error for logfile\n");
	}
	time_t curtime;

	struct tm t;

	while(1) {
		curtime = time(NULL);
		localtime_r(&curtime, &t);
		if(t.tm_sec == 0)
			do_command();
	}

	return 0;
}

void do_command(void) {
	char sentence[BUFSIZE];

	rewind(filefp);
	while(!feof(filefp)) {
		fgets(sentence, BUFSIZE, filefp); //한문장 읽어옴
		play_command(sentence);
	}

	return;
}

void play_command(char buf[]) {
	char *token;
	char tmpbuf[BUFSIZE];
	char command[BUFSIZE];
	struct tm t;
	time_t now;

	memset(s_min, 0, sizeof(s_min));
	memset(s_hour, 0, sizeof(s_hour));
	memset(s_day, 0, sizeof(s_day));
	memset(s_month, 0, sizeof(s_month));
	memset(s_wday, 0, sizeof(s_wday));
	memset(min, 0, sizeof(min));
	memset(hour, 0, sizeof(hour));
	memset(day, 0, sizeof(day));
	memset(month, 0, sizeof(month));
	memset(wday, 0, sizeof(wday));
	memset(tmpbuf, 0, BUFSIZE);

	strcpy(tmpbuf, buf);

	token = strtok(tmpbuf, " ");
	strcpy(s_min, token);
	check_cycle(s_min, 1);
	token = strtok(NULL, " ");
	strcpy(s_hour, token);
	check_cycle(s_hour, 2);
	token = strtok(NULL, " ");
	strcpy(s_day, token);
	check_cycle(s_day, 3);
	token = strtok(NULL, " ");
	strcpy(s_month, token);
	check_cycle(s_month, 4);
	token = strtok(NULL, " ");
	strcpy(s_wday, token);
	check_cycle(s_wday, 5);

	token = strtok(NULL, "\n");
	strcpy(command, token);

	now = time(NULL);
	localtime_r(&now, &t);
	
	if(min[t.tm_min] && hour[t.tm_hour] && day[t.tm_day] && month[t.tm_month+1] && wday[t.tm_wday])
		system(command);
	//시간이 모두 1이면 실행
	return;
}

void check_cycle(char arr[], int num) {
	int slash_loc;
	int dash_loc;
	int term;
	if(num == 1) { //분
		if(check_star(arr))
			memset(min, 1, sizeof(min));
		if(arr[0] == '*' && arr[1] == '/') {
			term = atoi(arr+2);
			for(int i = 0; i < sizeof(arr); i++) {
				if((i % term) == (term - 1))
					min[i] = 1;
			}
		}

		for(int i = 0; i < strlen(s_min); i++) {
			int tmp1 = atoi(s_min);
			for(int j = 0 ; j < strlen(s_min); j++) {
				if(s_min[j] == '-') {
					dash_loc = j;
					break;
				}
			}
			int tmp2 = atoi(s_min + dash_loc + 1);
			

		}



	}
	else if (num == 2) { //시간
		if(check_star(arr))
			memset(hour, 1, sizeof(hour));
		if(arr[0] == '*' && arr[1] == '/') {
			term = atoi(arr+2);
			for(int i = 0; i < sizeof(arr); i++) {
				if((i % term) == (term - 1))
					hour[i] = 1;
			}
		}
	}
	else if (num == 3) { //날짜
		if(check_star(arr))
			memset(day, 1, sizeof(day));
		if(arr[0] == '*' && arr[1] == '/') {
			term = atoi(arr+2);
			for(int i = 0; i < sizeof(arr); i++) {
				if((i % term) == (term - 1))
					day[i] = 1;
			}
		}
	}
	else if(num == 4) { //달
		if(check_star(arr))
			memset(month, 1, sizeof(month));
		if(arr[0] == '*' && arr[1] == '/') {
			term = atoi(arr+2);
			for(int i = 0; i < sizeof(arr); i++) {
				if((i % term) == (term - 1))
					month[i] = 1;
			}
		}

	}
	else if (num == 5) { //요일
		if(check_star(arr))
			memset(wday, 1, sizeof(wday));
		if(arr[0] == '*' && arr[1] == '/') {
			term = atoi(arr+2);
			for(int i = 0; i < sizeof(arr); i++) {
				if((i % term) == (term - 1))
					wday[i] = 1;
			}
		}
	}
}

int check_star(char arr[]) {
	if(!strcmp(arr, "*"))
		return 1;
	else
		return 0;
}