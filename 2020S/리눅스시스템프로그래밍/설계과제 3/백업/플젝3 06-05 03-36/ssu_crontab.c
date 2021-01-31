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

	setbuf(filefp, NULL);
	
	if((logfp = fopen("ssu_crontab_log", "a+")) < 0) {
		fprintf(stderr, "log file fopen error\n");
		exit(1);
	}

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

		if(!strcmp(reserve[0], todo))
			add_command();
		else if(!strcmp(reserve[1], todo))
			remove_command();
		else if(!strcmp(reserve[2], todo))
			break;
	}

	gettimeofday(&end_t, NULL);
	ssu_runtime(&begin_t, &end_t);
	exit(0);
}

void add_command(void) {
	char *token;
	char min[10];
	char hour[10];
	char day[10];
	char month[10];
	char wday[10];
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
/*
	token = strtok(input, " "); //명령어 컷

	token = strtok(NULL, " ");
	strcpy(min, token);
	if(check_correct(min, 1)) {
		printf("minute input error!\n");
		return;
	}

	token = strtok(NULL, " ");
	strcpy(hour, token);
	if(check_correct(hour, 2)) {
		printf("hour input error!\n");
		return;
	}

	token = strtok(NULL, " ");
	strcpy(day, token);
	if(check_correct(day, 3)) {
		printf("day input error!\n");
		return;
	}

	token = strtok(NULL, " ");
	strcpy(month, token);
	if(check_correct(month, 4)) {
		printf("month input error!\n");
		return;
	}

	token = strtok(NULL, " ");
	strcpy(wday, token);
	if(check_correct(wday, 5)) {
		printf("weekday input error!\n");
		return;
	}
*/
	fseek(filefp, 0, SEEK_END);
	fwrite(command, strlen(command), 1, filefp);

	return;
}

void remove_command(void) {
	int num = atoi(command);
	if(num > crontabnum) {
		printf("number is too big!\n");
		return;
	}





}

int check_correct(char arr[], int index) {
	if(index == 1) { //min

	}
	else if(index == 2) { //hour
		
	}
	else if(index == 3) { //day

	}
	else if(index == 4) { //month

	}
	else if(index == 5) { //wday

	}
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