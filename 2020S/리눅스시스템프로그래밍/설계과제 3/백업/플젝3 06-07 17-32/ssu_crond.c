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
void write_log(char buf[]);


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

	//여기부터 디몬이 할일 짜기

	//시간을 읽어서 초가 00이면 시작

	if((filefp = fopen("ssu_crontab_file", "r")) == NULL) {
		fprintf(stderr, "fopen error for command file\n");
		exit(1);
	}

	if((logfp = fopen("ssu_crontab_log", "a+")) == NULL) {
		fprintf(stderr, "fopen error for logfile\n");
	}
	setbuf(logfp, NULL);

	time_t prevtime, curtime;

	struct tm t1, t2;

	prevtime = time(NULL);

	while(1) {
		localtime_r(&prevtime, &t1);
		curtime = time(NULL);
		localtime_r(&curtime, &t2);
		if(t1.tm_min + 1 == t2.tm_min) {
			prevtime = curtime;
			do_command();
		}
		sleep(1);
	}

	return 0;
}

void do_command(void) {
	char sentence[BUFSIZE];

	rewind(filefp);
	while(fgets(sentence, BUFSIZE, filefp) != NULL) { //한문장 읽어옴
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
	//fputs(tmpbuf, stdout);

	token = strtok(tmpbuf, " ");
	strcpy(s_min, token);

	token = strtok(NULL, " ");
	strcpy(s_hour, token);

	token = strtok(NULL, " ");
	strcpy(s_day, token);

	token = strtok(NULL, " ");
	strcpy(s_month, token);

	token = strtok(NULL, " ");
	strcpy(s_wday, token);

	token = strtok(NULL, "\n");
	strcpy(command, token);

	check_cycle(s_min, 1);
	check_cycle(s_hour, 2);
	check_cycle(s_day, 3);
	check_cycle(s_month, 4);
	check_cycle(s_wday, 5);

	now = time(NULL);
	localtime_r(&now, &t);
	
	if(min[t.tm_min] && hour[t.tm_hour] && day[t.tm_mday] && month[t.tm_mon+1] && wday[t.tm_wday]) {
		system(command);
		write_log(buf);
	}
	//시간이 모두 1이면 실행
	return;
}

void write_log(char buf[]) {
	time_t curtime;
	char tmp[BUFSIZE];
	memset(tmp, 0, BUFSIZE);
	curtime = time(NULL);
	sprintf(tmp, "[%s", ctime(&curtime));
	tmp[strlen(tmp) - 1] = ']';
	strcat(tmp, " run ");
	strcat(tmp, buf);
	fputs(tmp, logfp);

	return;
}


void check_cycle(char arr[], int num) {
	int slash_loc = -1;
	int dash_loc = -1;
	int term;
	char *ptr;
	char buf[20][20];
	char tmp[100];
	int i = 0;
	int cnt = 0;
	int checksum = 0;

	memset(buf, 0, sizeof(buf));

	strcpy(tmp, arr);
	ptr = strtok(tmp, ",");
	strcpy(buf[i++], ptr);
	cnt++;
	
	while((ptr = strtok(NULL, ","))!= NULL) {
		strcpy(buf[i++], ptr);
		cnt++;
	}

	//---------------여기까지 문제 없음---------------------------------
	for(i = 0; i < cnt; i++) {
		dash_loc = -1;
		slash_loc = -1;
		checksum = 0;

		if(num == 1) { //분

			if(check_star(buf[i])) {
				memset(min, 1, sizeof(min));
				return;
			}
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				term = atoi(buf[i]+2);
				for(int i = 0; i < sizeof(min); i++) {
					if((i % term) == (term - 1))
						min[i] = 1;
				}
				return;
			}

			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-' || buf[i][x] == '/')
					checksum = 1;
			} //쉼표로 뽀갠것이 숫자일떄

			if(!checksum) {
				int tmp = atoi(buf[i]);
				min[tmp] = 1;
				return;
			} //그 숫자 ON

			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-') {
					dash_loc = x;
					break;
				}
			}
			checksum = 0;
			if(dash_loc != -1) { //dash 가 있을때
				int start = atoi(buf[i]);
				int end = atoi(buf[i] + dash_loc + 1);
				for(int k = 0; k < strlen(buf[i]); k++) {
					if(buf[i][k] == '/') {
						checksum = 1;
						slash_loc = k;
						break;
					}
				}
				if(checksum) { // slash가 있을떄
					int div = atoi(buf[i]+slash_loc + 1);
					int hop = 0;
					for(int s = start; s <= end; s++) {
						hop++;
						if(hop % div == 0)
							min[s] = 1;
					}
				}
				else { //slash가 뒤에 없을떄
					for(int s = start; s<= end; s++)
						min[s] = 1;
				}
			}
		}
		else if (num == 2) { //시간
			if(check_star(buf[i])) {
				memset(hour, 1, sizeof(hour));
				return;
			}
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				term = atoi(buf[i]+2);
				for(int i = 0; i < sizeof(hour); i++) {
					if((i % term) == (term - 1))
						hour[i] = 1;
				}
				return;
			}
			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-' || buf[i][x] == '/')
					checksum = 1;
			} //쉼표로 뽀갠것이 숫자일떄
			if(!checksum) {
				int tmp = atoi(buf[i]);
				hour[tmp] = 1;
				return;
			} //그 숫자 ON

			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-') {
					dash_loc = x;
					break;
				}
			}
			checksum = 0;
			if(dash_loc != -1) { //dash 가 있을때
				int start = atoi(buf[i]);
				int end = atoi(buf[i] + dash_loc + 1);
				for(int k = 0; k < strlen(buf[i]); k++) {
					if(buf[i][k] == '/') {
						checksum = 1;
						slash_loc = k;
						break;
					}
				}
				if(checksum) { // slash가 있을떄
					int div = atoi(buf[i]+slash_loc + 1);
					int hop = 0;
					for(int s = start; s <= end; s++) {
						hop++;
						if(hop % div == 0)
							hour[s] = 1;
					}
					return;
				}
				else { //slash가 뒤에 없을떄
					for(int s = start; s<= end; s++)
						hour[s] = 1;
					return;
				}
			}
		}
		else if (num == 3) { //날짜
			if(check_star(buf[i])) {
				memset(day, 1, sizeof(day));
				return;
			}
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				term = atoi(buf[i]+2);
				for(int i = 0; i < sizeof(day); i++) {
					if((i % term) == (term - 1))
						day[i] = 1;
				}
				return;
			}
			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-' || buf[i][x] == '/')
					checksum = 1;
			} //쉼표로 뽀갠것이 숫자일떄
			if(!checksum) {
				int tmp = atoi(buf[i]);
				day[tmp] = 1;
				return;
			} //그 숫자 ON

			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-') {
					dash_loc = x;
					break;
				}
			}
			checksum = 0;
			if(dash_loc != -1) { //dash 가 있을때
				int start = atoi(buf[i]);
				int end = atoi(buf[i] + dash_loc + 1);
				for(int k = 0; k < strlen(buf[i]); k++) {
					if(buf[i][k] == '/') {
						checksum = 1;
						slash_loc = k;
						break;
					}
				}
				if(checksum) { // slash가 있을떄
					int div = atoi(buf[i]+slash_loc + 1);
					int hop = 0;
					for(int s = start; s <= end; s++) {
						hop++;
						if(hop % div == 0)
							day[s] = 1;
					}
					return;
				}
				else { //slash가 뒤에 없을떄
					for(int s = start; s<= end; s++)
						day[s] = 1;
					return;
				}
			}
		}
		else if(num == 4) { //달
			if(check_star(buf[i])) {
				memset(month, 1, sizeof(month));
				return;
			}
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				term = atoi(buf[i]+2);
				for(int i = 1; i < sizeof(month); i++) {
					if((i % term) == (term - 1))
						month[i] = 1;
				}
				return;
			}
			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-' || buf[i][x] == '/')
					checksum = 1;
			} //쉼표로 뽀갠것이 숫자일떄
			if(!checksum) {
				int tmp = atoi(buf[i]);
				month[tmp] = 1;
				return;
			} //그 숫자 ON

			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-') {
					dash_loc = x;
					break;
				}
			}
			checksum = 0;
			if(dash_loc != -1) { //dash 가 있을때
				int start = atoi(buf[i]);
				int end = atoi(buf[i] + dash_loc + 1);
				for(int k = 0; k < strlen(buf[i]); k++) {
					if(buf[i][k] == '/') {
						checksum = 1;
						slash_loc = k;
						break;
					}
				}
				if(checksum) { // slash가 있을떄
					int div = atoi(buf[i]+slash_loc + 1);
					int hop = 0;
					for(int s = start; s <= end; s++) {
						hop++;
						if(hop % div == 0)
							month[s] = 1;
					}
					return;
				}
				else { //slash가 뒤에 없을떄
					for(int s = start; s<= end; s++)
						month[s] = 1;
					return;
				}
			}

		}
		else if (num == 5) { //요일
			if(check_star(buf[i])) {
				memset(wday, 1, sizeof(wday));
				return;
			}
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				term = atoi(buf[i]+2);
				for(int i = 0; i < sizeof(wday); i++) {
					if((i % term) == (term - 1))
						wday[i] = 1;
				}
				return;
			}
			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-' || buf[i][x] == '/')
					checksum = 1;
			} //쉼표로 뽀갠것이 숫자일떄
			if(!checksum) {
				int tmp = atoi(buf[i]);
				wday[tmp] = 1;
				return;
			} //그 숫자 ON

			for(int x = 0; x < strlen(buf[i]); x++) {
				if(buf[i][x] == '-') {
					dash_loc = x;
					break;
				}
			}
			checksum = 0;
			if(dash_loc != -1) { //dash 가 있을때
				int start = atoi(buf[i]);
				int end = atoi(buf[i] + dash_loc + 1);
				for(int k = 0; k < strlen(buf[i]); k++) {
					if(buf[i][k] == '/') {
						checksum = 1;
						slash_loc = k;
						break;
					}
				}
				if(checksum) { // slash가 있을떄
					int div = atoi(buf[i]+slash_loc + 1);
					int hop = 0;
					for(int s = start; s <= end; s++) {
						hop++;
						if(hop % div == 0)
							wday[s] = 1;
					}
					return;
				}
				else { //slash가 뒤에 없을떄
					for(int s = start; s<= end; s++)
						wday[s] = 1;
					return;
				}
			}
		}
	}
	return;
}

int check_star(char arr[]) {
	if(!strcmp(arr, "*"))
		return 1;
	else
		return 0;
}