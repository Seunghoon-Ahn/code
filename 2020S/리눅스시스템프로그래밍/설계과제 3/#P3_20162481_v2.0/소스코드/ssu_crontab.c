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

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t); //프로그램 수행시간 측정
void print_crontabfile(void); //ssu_crontab_file에 쓰는 함수
int check_correct(char arr[], int index); //주기가 올바른지 확인하는 함수
void add_command(void); //명령어를 추가하는 함수
void remove_command(void); //명령어를 삭제하는 함수
int check_star(char arr[]); //주기가 *인지 확인하는 함수
int check_slash(char arr[]); //주기에 /가 포함되어있는지 확인하는 함수
int check_dash(char arr[]); //주기에 -가 포함되어있는지 확인하는 함수
void write_log(char arr[], char sentence[]); //log를 작성하는 함수

char const_input[BUFSIZE];
char input[BUFSIZE];
char command[BUFSIZE];
int crontabnum;
FILE *filefp; //ssu_crontab_file 파일 포인터
FILE *logfp; //ssu_crontab_log 파일 포인터
char *reserve[3] = {"add", "remove", "exit"};

int main(void)
{
	struct timeval begin_t, end_t;
	char todo[10]; //가장 앞의 명령어를 저장
	int i = 0, checksum = 0;
	int enter = 1;

	gettimeofday(&begin_t, NULL); //프로그램 시작 시간 저장

	if((filefp = fopen("ssu_crontab_file", "r+")) < 0) {
		filefp = fopen("ssu_crontab_file", "w+");
		fclose(filefp);
		filefp = fopen("ssu_crontab_file", "r+");
	} //file 파일을 오픈함
	
	if((logfp = fopen("ssu_crontab_log", "a+")) < 0) {
		fprintf(stderr, "log file fopen error\n");
		exit(1);
	} //로그 파일을 오픈함
	setbuf(filefp, NULL);
	setbuf(stdout, NULL);
	setbuf(logfp, NULL);
	//버퍼를 NULL로 설정

	while(1) {
		memset(const_input, 0, BUFSIZE);
		memset(input, 0, BUFSIZE);
		memset(todo, 0, sizeof(todo));
		memset(command, 0, sizeof(command));
		if(enter)
			print_crontabfile(); //file의 내용을 출력함
		enter = 1;
		printf("20162481>"); //프롬프트를 구성함
		fgets(input, BUFSIZE, stdin);
		strcpy(const_input, input);
		i = 0;
		if(input[0] == '\n') {
			enter = 0;
			continue;
		}
		//개행 입력하면 프롬프트 재출력
		while(input[i] != ' ' && input[i] != '\n') {
			todo[i] = input[i];
			i++;
		}
		strcpy(command, input + i + 1);
		//사용자가 입력한것을 add remove 부분과 뒷부분을 분리
		checksum = 0;
		for(i = 0; i < 3; i++) {
			if(!strcmp(reserve[i], todo))
				checksum += (i + 1);
		}
		if(!checksum) {
			fprintf(stderr, "command error!\n");
			continue;
		} //add remove exit 이외의 명령일 경우 무시

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

void add_command(void) { //add를 실행하는 함수
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
	//배열 초기화
	
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
	//입력된 문장을 각각의 주기에 맞게 분해하여 각 주기가 올바른지 확인함

	fseek(filefp, 0, SEEK_END);
	fwrite(command, strlen(command), 1, filefp); //file에 새로 명령어를 씀

	write_log("add", command); //로그 작성
	return;
}

void remove_command(void) { //remove를 수행하는 함수
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
	//삭제할 문장의 시작점과 그 다음 문장의 시작점을 저장함

	memset(save, 0, BUFSIZE);
	if(fread(save, BUFSIZE, 1,filefp) < 0) {
		fprintf(stderr, "fread error!\n");
		return;
	} //삭제할 문장의 시작점부터 그 다음문장을 덮어씀
	fseek(filefp, del_loc, SEEK_SET);
	fwrite(save, BUFSIZE, 1, filefp);
	truncate("ssu_crontab_file", filesize - strlen(del_command));
	//파일에서 삭제한만큼 파일의 크기를 줄임
	write_log("remove", del_command); //로그 작성
	return;

}

int check_correct(char arr[], int index) { //주기가 올바른지 확인하는 함수
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
	//쉼표 단위로 주기를 분해함

	while((ptr = strtok_r(NULL, ",", &sav)) != NULL) {
		strcpy(buf[i++], ptr);
		cnt++;
	} //쉼표를 기준으로 토큰으로 분해

	for(i = 0; i < cnt; i++) { //분해한 것 각각을 분석함
		dash_loc = -1;
		slash_loc = -1;
		checksum = 0;

		for(int f = 0; f < strlen(buf[i]) - 1; f++) {
			if((buf[i][f] == '/' || buf[i][f] == '-') && (buf[i][f+1] == '-' || buf[i][f+1] == '/'))
				return 1;
		} //'-''/'기호가 2개이상 나올 경우 무조건 불가능한 주기

		if(index == 1) { // 분 확인
			if(check_star(buf[i])) return 0; // *만 있으면 ok
			
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				checksum = check_slash(buf[i] + 2);
				checksum = check_dash(buf[i] + 2);

				if(checksum) return 1;
				int temp = atoi(buf[i]+2);
				if(temp < 0 || temp > 60) return 1;         
			} // '*/'로 시작하는 경우 뒤에 숫자만 올 수 있음

			if(check_dash(buf[i])) { //문장에 '-'가 있을때
				int loc = check_dash(buf[i]);
				int tmp1 = atoi(buf[i]);
				int tmp2 = atoi(buf[i] + loc + 1);
				if(tmp1 >= tmp2) return 1;
				if(tmp1 < 0 || tmp2 > 60) return 1;
				
				loc = check_slash(buf[i]+ loc + 1);
				if(loc) { //문장에 '/'도 포함되어있는 경우 
					int tmp3 = atoi(buf[i] + loc + 1);
					if(tmp3 > tmp2 - tmp1) return 1;
				}
			}
			else if(!check_dash(buf[i]) && !check_slash(buf[i])) {
				int tmp1 = atoi(buf[i]);
				if(tmp1 < 0 || tmp1 > 60) return 1;
			} //문장에 - / 가 없는 경우 숫자만 판단함
			return 0;
		}
		else if (index == 2) { //시간 확인
			if(check_star(buf[i])) return 0; // *만 있으면 ok
			
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				checksum = check_slash(buf[i] + 2);
				checksum = check_dash(buf[i] + 2);

				if(checksum) return 1;
				int temp = atoi(buf[i]+2);
				if(temp < 0 || temp > 23) return 1; 
			} //문장이 */로 시작하는 경우 뒤에 숫자만 올수 있음

			if(check_dash(buf[i])) { //문장에 -가 있을때
				int loc = check_dash(buf[i]);
				int tmp1 = atoi(buf[i]);
				int tmp2 = atoi(buf[i] + loc + 1);
				if(tmp1 >= tmp2) return 1;
				if(tmp1 < 0 || tmp2 > 23) return 1;
				
				loc = check_slash(buf[i]+ loc + 1);
				if(loc) { //같은 문장에 /도 포함되어있을때
					int tmp3 = atoi(buf[i] + loc + 1);
					if(tmp3 > tmp2 - tmp1) return 1;
				}
			}
			else if(!check_dash(buf[i]) && !check_slash(buf[i])) {
				int tmp1 = atoi(buf[i]);
				if(tmp1 < 0 || tmp1 > 23) return 1;
			} //문장에 -또는 /가 없을 때
			return 0;
		}
		else if(index == 3) { //날짜 확인
			if(check_star(buf[i])) return 0; // *만 있으면 ok
			
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				checksum = check_slash(buf[i] + 2);
				checksum = check_dash(buf[i] + 2);

				if(checksum) return 1;
				int temp = atoi(buf[i]+2);
				if(temp < 1 || temp > 31) return 1;         
			} //문장이 */로 시작하는 경우 뒤에 숫자만 올 수 있음

			if(check_dash(buf[i])) { //문장에 -가 있는 경우
				int loc = check_dash(buf[i]);
				int tmp1 = atoi(buf[i]);
				int tmp2 = atoi(buf[i] + loc + 1);
				if(tmp1 >= tmp2) return 1;
				if(tmp1 < 1 || tmp2 > 31) return 1;
				
				loc = check_slash(buf[i]+ loc + 1);
				if(loc) { //같은 문장에 /도 포함되어있는 경우
					int tmp3 = atoi(buf[i] + loc + 1);
					if(tmp3 > tmp2 - tmp1) return 1;
				}
			}
			else if(!check_dash(buf[i]) && !check_slash(buf[i])) {
				int tmp1 = atoi(buf[i]);
				if(tmp1 < 1 || tmp1 > 31) return 1;
			} //문장에 -또는 /기호가 없을 경우
			return 0;
		}
		else if(index == 4) { //월 확인
			if(check_star(buf[i])) return 0; // *만 있으면 ok
			
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				checksum = check_slash(buf[i] + 2);
				checksum = check_dash(buf[i] + 2);

				if(checksum) return 1;
				int temp = atoi(buf[i]+2);
				if(temp < 1 || temp > 12) return 1; 
			} //문장이 */로 시작하는 경우 뒤에 숫자만 올 수 있음

			if(check_dash(buf[i])) { //문장에 -가 포함되어있는 경우
				int loc = check_dash(buf[i]);
				int tmp1 = atoi(buf[i]);
				int tmp2 = atoi(buf[i] + loc + 1);
				if(tmp1 >= tmp2) return 1;
				if(tmp1 < 1 || tmp2 > 12) return 1;
				
				loc = check_slash(buf[i]+ loc + 1);
				if(loc) { //문장에 /도 포함되어 있는 경우
					int tmp3 = atoi(buf[i] + loc + 1);
					if(tmp3 > tmp2 - tmp1) return 1;
				}
			}
			else if(!check_dash(buf[i]) && !check_slash(buf[i])) {
				int tmp1 = atoi(buf[i]);
				if(tmp1 < 1 || tmp1 > 12) return 1;
			} //문장에 -또는 /가 포함되어 있지 않은 경우 숫자만 판단함
			return 0;
		}
		else if(index == 5) { //요일 확인
			if(check_star(buf[i])) return 0; // *만 있으면 ok
			
			if(buf[i][0] == '*' && buf[i][1] == '/') {
				checksum = check_slash(buf[i] + 2);
				checksum = check_dash(buf[i] + 2);

				if(checksum) return 1;
				int temp = atoi(buf[i]+2);
				if(temp < 0 || temp > 6) return 1;  
			} //문장이 */로 시작하는 경우 뒤에 숫자만 올 수 있음

			if(check_dash(buf[i])) { //문장에 -가 포함되어 있을때
				int loc = check_dash(buf[i]);
				int tmp1 = atoi(buf[i]);
				int tmp2 = atoi(buf[i] + loc + 1);
				if(tmp1 >= tmp2) return 1;
				if(tmp1 < 0 || tmp2 > 6) return 1;
				
				loc = check_slash(buf[i]+ loc + 1);
				if(loc) { //문장에 /가 포함되어 있는 경우
					int tmp3 = atoi(buf[i] + loc + 1);
					if(tmp3 > tmp2 - tmp1) return 1;
				}
			}
			else if(!check_dash(buf[i]) && !check_slash(buf[i])) {
				int tmp1 = atoi(buf[i]);
				if(tmp1 < 0 || tmp1 > 6) return 1;
			} //문장에 - 또는 /가 포함되지 않은 경우
			return 0;
		}
	}
}

int check_dash(char arr[]) { //문장에 '-' 기 포함되었는지 확인하는 함수
	int i;
	for(i = 0; i < strlen(arr); i++) {
		if(*(arr + i) == '-')
			return i;
	}
	return 0;
}

int check_slash(char arr[]) { //문장에 '/' 가 포함되었는지 확인하는 함수
	int i;
	for(i = 0; i <strlen(arr); i++) {
		if(*(arr + i) == '/')
			return i;
	}
	return 0;
}

int check_star(char arr[]) { //문장에 *만 포함되어 있는지 확인하는 함수
	if(!strcmp(arr, "*"))
		return 1;
	else
		return 0;
}

void write_log(char arr[], char sentence[]) { //명령어를 로그에 작성하는 함수
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

void print_crontabfile(void) { //입력받은 명령어를 파일에 쓰는 함수
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
{ //프로그램의 수행시간 측정
	end_t->tv_sec -= begin_t->tv_sec; //끝난 시간에서 처음시간을 뺌

	if(end_t->tv_usec < begin_t->tv_usec){
		end_t->tv_sec--;
		end_t->tv_usec += 1000000;
	} //나중의 us값이 작을경우 1초를 뺴서 us값이 더해줌

	end_t->tv_usec -= begin_t->tv_usec;
	printf("Runtime: %ld:%02ld:%06ld(min:sec:usec)\n",
		end_t->tv_sec / 60, end_t->tv_sec % 60, end_t->tv_usec);
} //프로그램 수행시간을 분, 초, 마이크로초로 출력