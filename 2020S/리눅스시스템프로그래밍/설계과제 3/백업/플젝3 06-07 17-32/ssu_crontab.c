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

#define BUFSIZE 1024

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);
void print_crontabfile(void);
int check_correct(char arr[], int index);
void add_command(void);
void remove_command(void);
int check_star(char arr[]);
int check_slash(char arr[]);
int check_dash(char arr[]);
void write_log(char arr[], char sentence[]);

char const_input[BUFSIZE];
char input[BUFSIZE];
char command[BUFSIZE];
int crontabnum;
FILE *filefp;
FILE *logfp;
char *reserve[3] = {"add", "remove", "exit"};

int main(void)
{
	struct timeval begin_t, end_t;
	char todo[10]; //가장 앞의 명령어를 저장
	int i = 0, checksum = 0;

	gettimeofday(&begin_t, NULL);

	if((filefp = fopen("ssu_crontab_file", "r+")) < 0) {
		filefp = fopen("ssu_crontab_file", "w+");
		fclose(filefp);
		filefp = fopen("ssu_crontab_file", "r+");
	}
	
	if((logfp = fopen("ssu_crontab_log", "a+")) < 0) {
		fprintf(stderr, "log file fopen error\n");
		exit(1);
	}
	setbuf(filefp, NULL);
	setbuf(stdout, NULL);
	setbuf(logfp, NULL);
	
	while(1) {
		memset(const_input, 0, BUFSIZE);
		memset(input, 0, BUFSIZE);
		memset(todo, 0, sizeof(todo));
		memset(command, 0, sizeof(command));

		print_crontabfile();
		printf("20162481>");
		fgets(input, BUFSIZE, stdin);
		strcpy(const_input, input);
		i = 0;
		if(input[0] == '\n')
			continue;

		while(input[i] != ' ' && input[i] != '\n') {
			todo[i] = input[i];
			i++;
		}
		strcpy(command, input + i + 1);

		checksum = 0;
		for(i = 0; i < 3; i++) {
			if(!strcmp(reserve[i], todo))
				checksum += (i + 1);
		}
		if(!checksum) {
			fprintf(stderr, "command error!\n");
			continue;
		}

		if(!strcmp(reserve[0], todo)) //add일떄
			add_command();
		else if(!strcmp(reserve[1], todo)) //remove 일떄
			remove_command();
		else if(!strcmp(reserve[2], todo)) //exit일떄
			break;
	}

	gettimeofday(&end_t, NULL);
	ssu_runtime(&begin_t, &end_t);
	exit(0);
}

void add_command(void) {
	char *token;
	char *tmptmp;
	char min[20];
	char hour[20];
	char day[20];
	char month[20];
	char wday[20];
	int checksum;

	memset(min, 0, sizeof(min));
	memset(hour, 0, sizeof(hour));
	memset(day, 0, sizeof(day));
	memset(month, 0, sizeof(month));
	memset(wday, 0, sizeof(wday));

	checksum = 0;
	for(int i = 0; i < strlen(input); i++)
		if(input[i] == ' ' || input[i] == '\n')
			checksum++;


	if(checksum < 7) {
		printf("Input error!\n");
		return;
	}

	token = strtok_r(input, " ", &tmptmp); //명령어 컷

	token = strtok_r(NULL, " ", &tmptmp);
	strcpy(min, token);
	if(check_correct(min, 1)) {
		printf("minute input error!\n");
		return;
	}

	token = strtok_r(NULL, " ", &tmptmp);
	strcpy(hour, token);
	if(check_correct(hour, 2)) {
		printf("hour input error!\n");
		return;
	}

	token = strtok_r(NULL, " ", &tmptmp);
	strcpy(day, token);
	if(check_correct(day, 3)) {
		printf("day input error!\n");
		return;
	}

	token = strtok_r(NULL, " ", &tmptmp);
	strcpy(month, token);
	if(check_correct(month, 4)) {
		printf("month input error!\n");
		return;
	}

	token = strtok_r(NULL, " ", &tmptmp);
	strcpy(wday, token);
	if(check_correct(wday, 5)) {
		printf("weekday input error!\n");
		return;
	}

	fseek(filefp, 0, SEEK_END);
	fwrite(command, strlen(command), 1, filefp);

	write_log("add", command);
	return;
}

void remove_command(void) {
	int i = 0;
	int num = atoi(command);
	int del_loc = 0; //삭제할 문장의 시작 위치
	int next_loc = 0; //삭제할 문장 다음줄의 시작 위치
	char tmp[BUFSIZE];
	char save[BUFSIZE];
	char del_command[BUFSIZE];
	int filesize;

	if(command[0] == '\n' || command[0] == '\0') {
		printf("No number!!\n");
		return;
	}
	if(num >= crontabnum || num < 0) {
		printf("number error!!!\n");
		return;
	}

	fseek(filefp, 0, SEEK_END);
	filesize = ftell(filefp); //원래의 파일 크기 구하기
	fseek(filefp, 0, SEEK_SET);

	for(i = 0; i < num; i++) {
		memset(tmp, 0, BUFSIZE);
		fgets(tmp, BUFSIZE, filefp);
		del_loc += strlen(tmp);
	}
	memset(tmp, 0, BUFSIZE);
	memset(del_command, 0, BUFSIZE);
	fgets(del_command, BUFSIZE, filefp);
	next_loc = ftell(filefp);
	memset(save, 0, BUFSIZE);
	if(fread(save, BUFSIZE, 1,filefp) < 0) {
		fprintf(stderr, "fread error!\n");
		return;
	}
	fseek(filefp, del_loc, SEEK_SET);
	fwrite(save, BUFSIZE, 1, filefp);
	truncate("ssu_crontab_file", filesize - strlen(del_command));

	write_log("remove", del_command);
	return;

}

int check_correct(char arr[], int index) {
	int checksum = 0;
	int slash_loc = -1;
	int dash_loc = -1;
	int length;
	char buf[20][20];
	char tmp[100];
	char *ptr, *sav;
	int i = 0;
	int cnt = 0;
	memset(buf, 0, sizeof(buf));
	memset(tmp, 0, sizeof(tmp));

	strcpy(tmp, arr);
	ptr = strtok_r(tmp, ",", &sav);
	strcpy(buf[i++], ptr);
	cnt++;

	while((ptr = strtok_r(NULL, ",", &sav)) != NULL) {
		strcpy(buf[i++], ptr);
		cnt++;
	} //쉼표를 기준으로 토큰으로 분해

	for(i = 0; i < cnt; i++) {
		dash_loc = -1;
		slash_loc = -1;
		checksum = 0;

		if(index == 1) { // 분 확인
			if(check_star(buf[i])) return 0; // *만 있으면 ok
			
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				checksum = check_slash(buf[i] + 2);
				checksum = check_dash(buf[i] + 2);
			}

		}
		else if (index == 2) {

		}
		else if(index == 3) {

		}
		else if(index == 4) {

		}
		else if(index == 5) {

		}
	}




}

int check_dash(char arr[]) {
	int i;
	for(i = 0; i < strlen(arr); i++) {
		if(*arr + i == '-')
			return 1;
	}
	return 0;
}

int check_slash(char arr[]) {
	int i;
	for(i = 0; i <strlen(arr); i++) {
		if(*arr + i == '/')
			return 1;
	}
	return 0;
}


int check_star(char arr[]) {
	if(!strcmp(arr, "*"))
		return 1;
	else
		return 0;
}

void write_log(char arr[], char sentence[]) {
	time_t curtime;
	char timebuf[BUFSIZE];

	memset(timebuf, 0, BUFSIZE);
	curtime = time(NULL);
	sprintf(timebuf, "[");
	sprintf(timebuf+1, "%s", ctime(&curtime));
	timebuf[strlen(timebuf)-1] = ']';
	strcat(timebuf, " ");
	strcat(timebuf, arr);
	strcat(timebuf, " ");
	strcat(timebuf, sentence);

	fwrite(timebuf, strlen(timebuf), 1, logfp);

	return;
}

void print_crontabfile(void) {
	char tmp[BUFSIZE];
	memset(tmp, 0, BUFSIZE);

	int num = 0;
	fseek(filefp, 0, SEEK_SET);
	while(fgets(tmp, BUFSIZE, filefp) != NULL) {
		printf("%d. ", num);
		fputs(tmp, stdout);
		num++;
	}
	printf("\n");
	crontabnum = num; //crontabfile에 있는 갯수를 저장
	return;
}




void ssu_runtime(struct timeval *begin_t, struct timeval *end_t)
{ 
	end_t->tv_sec -= begin_t->tv_sec; //끝난 시간에서 처음시간을 뺌

	if(end_t->tv_usec < begin_t->tv_usec){
		end_t->tv_sec--;
		end_t->tv_usec += 1000000;
	} //나중의 us값이 작을경우 1초를 뺴서 us값이 더해줌

	end_t->tv_usec -= begin_t->tv_usec;
	printf("Runtime: %ld:%02ld:%06ld(min:sec:usec)\n",
		end_t->tv_sec / 60, end_t->tv_sec % 60, end_t->tv_usec);
} //프로그램 수행시간을 분, 초, 마이크로초로 출력