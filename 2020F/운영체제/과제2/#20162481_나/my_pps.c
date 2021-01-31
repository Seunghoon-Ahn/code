#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdbool.h>
#include <dirent.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <sys/ioctl.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define NAS 100

typedef long long ll;

typedef struct {
	char user[50];
	int pid;
	double cpu;
	double mem;
	int vsz;
	int rss;
	char tty[10];
	char status[10];
	char stime[10];
	char time[10];
	char command[100];
}psset; // 프로세스의 정보를 담는 구조체

void pps(void);
psset read_info(int fname);
void print_info(psset pcs);
void print_title(void);
double calcul_cpu(ll value_stat[]);
double calcul_mem(int fname);
int calcul_rss(int fname);
double calcul_uptime(void);
void calcul_stime(ll value_stat[]); 
void calcul_systime(ll value_stat[]);
void calcul_stat(ll value_stat[]);
void calcul_user(int fname);
void calcul_tty(ll value_stat[]);
int cmp(const struct dirent ** a, const struct dirent ** b);
static int f_function(const struct dirent *dir);

bool a_check = false;
bool u_check = false;
bool x_check = false;
//옵션 체크 함수

char stime_sav[6];
char systime_sav[6];
char stat_sav[6];
char user_sav[10];
char tty_sav[10];

int width; //화면 크기 저장
int idc = 0;
//옵션을 숫자로 환산
int main(int argc, char *argv[]) {
	int i;

	if(argc == 2) {
		for(i = 0; i < strlen(argv[1]); i++) {
			if(argv[1][i] == 'a')
				a_check = true;
			else if(argv[1][i] == 'u')
				u_check = true;
			else if(argv[1][i] == 'x')
				x_check = true;
		}
	} //옵션이 입력되면 옵션을 분석함

	if(a_check == true)
		idc += 4;
	if(u_check == true)
		idc += 2;
	if(x_check == true)
		idc += 1;
	struct winsize sz;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &sz);
	width = sz.ws_col + 1; //창 가로크기 계산
	pps();
	return 0;
}

void pps(void) { //pps 전체 함수
	struct dirent **namelist;
	int count;
	int idx;
	char path[100] = "/proc";
	psset res;

	if((count = scandir(path, &namelist, f_function, cmp)) == -1) {
		fprintf(stderr, "scandir error!\n");
		return;
	} //proc 디렉터리 스캔
	int i;
	print_title();
	// title 출력 하는 함수 만들기
	for(i = 0; i < count; i++) {
		int fname = atoi(namelist[i]->d_name);
		if(fname <= 0)
			continue;
		res = read_info(fname);
		print_info(res);
	} //프로세스 하나씩 읽어서 출력

	for(i = 0; i < count; i++)
		free(namelist[i]);
	free(namelist);

	return;
}

static int f_function(const struct dirent *dir) { //scandir 필터함수
	if(isdigit(dir->d_name[0]))
		return 1;
	else
		return 0;
}

int cmp(const struct dirent **a, const struct dirent **b) { //scandir sort 함수
	int x = atoi((*a)->d_name);
	int y = atoi((*b)->d_name);
	return x > y;
}// 수정필요

void print_title(void) { // 상단 목록 출력하는 함수
	if(idc == 0)
		printf("   PID TTY          TIME CMD\n");
	else if(idc == 1 || idc == 4 || idc == 5)
		printf("   PID TTY      STAT   TIME COMMAND\n");
	else if(idc == 2 || idc == 3 || idc == 6 || idc == 7)
		printf("USER        PID %%CPU %%MEM     VSZ    RSS TTY    STAT START   TIME COMMAND\n");

	return;
}

void print_info(psset pcs) { //프로세스 정보를 출력하는 함수
	char for_print[1024];
	memset(for_print, 0, sizeof(for_print));
	struct passwd *user_info;
	user_info = getpwuid(getuid());

	if(idc == 0) { //ps
		char* curtty = ttyname(STDERR_FILENO);
		curtty = curtty + 5;
		if(strcmp(curtty, pcs.tty))
			return;
		snprintf(for_print, width, "%6d %-8s %02d:%02d:%s %s", pcs.pid, pcs.tty, atoi(pcs.time)/60, atoi(pcs.time)%60, pcs.time+3, pcs.command);
		printf("%s\n", for_print);
		return;
	}
	else if (idc == 1) { //ps x
		if(strcmp(user_info->pw_name, pcs.user))
			return;
		snprintf(for_print, width, "%6d %-8s %-5s %s %s", pcs.pid, pcs.tty, pcs.status, pcs.time, pcs.command);
		printf("%s\n", for_print);
		return;
	}
	else if (idc == 2) { //ps u
		if(strcmp(user_info->pw_name, pcs.user))
			return;
		if(!strcmp(pcs.tty, "?"))
			return;
		snprintf(for_print, width, "%-8s %6d %4.1lf %4.1lf %7d %6d %-6s %-4s %5s %5s %s", 
			pcs.user, pcs.pid, pcs.cpu, pcs.mem, pcs.vsz, pcs.rss, pcs.tty, pcs.status, pcs.stime, pcs.time, pcs.command);
		printf("%s\n", for_print);
	}
	else if (idc == 3) { //ps ux
		if(strcmp(user_info->pw_name, pcs.user))
			return;
		snprintf(for_print, width, "%-8s %6d %4.1lf %4.1lf %7d %6d %-6s %-4s %5s %5s %s", 
			pcs.user, pcs.pid, pcs.cpu, pcs.mem, pcs.vsz, pcs.rss, pcs.tty, pcs.status, pcs.stime, pcs.time, pcs.command);
		printf("%s\n", for_print);
	}
	else if (idc == 4) { //ps a
		if(!strcmp(pcs.tty, "?"))
			return;
		snprintf(for_print, width, "%6d %-8s %-5s %s %s", pcs.pid, pcs.tty, pcs.status, pcs.time, pcs.command);
		printf("%s\n", for_print);
		return;   
	}
	else if (idc == 5) { //ps ax
		snprintf(for_print, width, "%6d %-8s %-5s %s %s", pcs.pid, pcs.tty, pcs.status, pcs.time, pcs.command);
		printf("%s\n", for_print);
		return; 
	}
	else if (idc == 6) { //ps au
		if(!strcmp(pcs.tty, "?"))
			return;
		snprintf(for_print, width, "%-8s %6d %4.1lf %4.1lf %7d %6d %-6s %-4s %5s %5s %s", 
			pcs.user, pcs.pid, pcs.cpu, pcs.mem, pcs.vsz, pcs.rss, pcs.tty, pcs.status, pcs.stime, pcs.time, pcs.command);
		printf("%s\n", for_print);    
	}
	else if (idc == 7) { //ps aux
		snprintf(for_print, width, "%-8s %6d %4.1lf %4.1lf %7d %6d %-6s %-4s %5s %5s %s", 
			pcs.user, pcs.pid, pcs.cpu, pcs.mem, pcs.vsz, pcs.rss, pcs.tty, pcs.status, pcs.stime, pcs.time, pcs.command);
		printf("%s\n", for_print);      
	}
	//옵션에 따라 다른 형식으로 출력
	return;
}

psset read_info(int fname) { //프로세스의 정보를 읽어오는 함수
	char path[50] = "/proc/";
	char tmp[150] = {0, };
	char tmptmp[NAS] = {0, };
	char tmptmptmp[NAS] = {0, };
	long long value_stat[54] = {0, };
	int i = 0;

	sprintf(tmp, "%d", fname);
	strcat(path, tmp);
	memset(tmp, 0, sizeof(tmp));
	memset(tmptmp, 0, sizeof(tmptmp));
	strcpy(tmp, path);
	strcat(tmp, "/stat");
	psset pcs;
	pcs.pid = fname; //pid 저장
	FILE *fp;

	if((fp = fopen(tmp, "r")) == NULL) {
		fprintf(stderr, "fopen error in read_info function with %d\n", fname);
		exit(1);
	}
	char tmpchar;
	fscanf(fp, "%lld", &value_stat[1]); //pid
	fscanf(fp, "%s", tmp); //이름
	memset(pcs.status, 0, sizeof(pcs.status));
	fscanf(fp, "%s", pcs.status); //3번쨰에 있는 status 문자를 구조체에 집어넣음
	for(i = 4; i <= 52; i++)
		fscanf(fp, "%lld", &value_stat[i]);
	//stat 파일 읽여왔음
	fclose(fp);

	memset(tmp, 0, sizeof(tmp));
	strcpy(tmp, path);
	strcat(tmp, "/cmdline");
	if((fp =fopen(tmp, "r")) == NULL) {
		fprintf(stderr, "fopen error2 in read_info\n");
		exit(1);
	}
	if(fgets(tmptmp, sizeof(tmptmp), fp) == NULL) {
		fclose(fp);
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, path);
		strcat(tmp, "/comm");
		if((fp = fopen(tmp, "r")) == NULL) {
			fprintf(stderr, "fopen error3 in read_info\n");
			exit(1);
		}
		tmptmp[0] = '[';
		fscanf(fp, "%s", tmptmp+1);
		strcat(tmptmp, "]");
	}

	for(i = 0;i < sizeof(tmptmp); i++)
		if(tmptmp[i] == '\0' && tmptmp[i+1] != '\0')
			tmptmp[i] = ' ';

	strcpy(pcs.command, tmptmp);

	calcul_user(fname);
	strcpy(pcs.user, user_sav);
	memset(user_sav, 0, sizeof(user_sav));

	pcs.cpu = calcul_cpu(value_stat);
	pcs.mem = calcul_mem(fname);
	pcs.vsz = value_stat[23] / 1024;
	pcs.rss = calcul_rss(fname);
	
	calcul_tty(value_stat);
	strcpy(pcs.tty, tty_sav); //tty
	memset(tty_sav, 0, sizeof(tty_sav));

	calcul_stat(value_stat);
	strcat(pcs.status, stat_sav); //stat
	memset(stat_sav, 0, sizeof(stat_sav));

	calcul_stime(value_stat);
	strcpy(pcs.stime, stime_sav); //stime
	memset(stime_sav, 0, sizeof(stime_sav));

	calcul_systime(value_stat);
	strcpy(pcs.time, systime_sav); //time
	memset(systime_sav, 0, sizeof(systime_sav));

	fclose(fp);
	return pcs;
}

void calcul_tty(ll value_stat[]) { //프로세스의 tty를 확인하는 함수
	int mj = major(value_stat[7]);
	int mi = minor(value_stat[7]);
	char path[NAS] = {0, };
	char oriname[10] = {0, };
	memset(path, 0, sizeof(path));
	memset(oriname, 0, sizeof(oriname));

	if(value_stat[7] == 0) {
		strcpy(tty_sav, "?");
		return;
	}
	sprintf(path, "/dev/char/%d:%d", mj, mi);
	if(access(path, F_OK) == 0) {
		readlink(path, oriname, sizeof(oriname));
		strcpy(tty_sav, oriname+3);
	}
	else {
		sprintf(oriname, "pts/%d", mi);
		strcpy(tty_sav, oriname);
	}

	return;
}

void calcul_user(int fname) { //유저 이름을 확인하는 함수
	FILE *fp;
	char tmp[10] = {0, };
	char arr[NAS] = {0, };
	char path[NAS] = "/proc/";
	char trash[10];
	int uid, tmp1, tmp2, tmp3;
	struct passwd *p;

	sprintf(tmp, "%d", fname);
	strcat(path, tmp);
	strcat(path, "/status");

	if((fp = fopen(path, "r")) == NULL) {
		fprintf(stderr, "fopen error in calcul_user\n");
		exit(1);
	}
	int i;
	for(i = 0; i < 8; i++)
		fgets(arr, sizeof(arr), fp);
	memset(arr, 0, sizeof(arr));
	
	fgets(arr, sizeof(arr), fp);
	sscanf(arr, "%s%d%d%d%d", trash, &uid, &tmp1, &tmp2, &tmp3);
	p = getpwuid(uid);

	if(strlen(p->pw_name) > 8) {
		strncpy(user_sav, p->pw_name, 7);
		strcat(user_sav, "+");
	}
	else
		strcpy(user_sav, p->pw_name);

	fclose(fp);
	return;
}

void calcul_stat(ll value_stat[]) { //status를 확인하는 함수
	FILE *fp;
	char path[NAS] = "/proc/";
	char tmp[NAS] = {0, };

	sprintf(tmp, "%lld", value_stat[1]);
	strcat(path, tmp);
	strcat(path, "/status");

	if(value_stat[19] > 0)
		strcat(stat_sav, "N");
	else if (value_stat[19] < 0)
		strcat(stat_sav, "<");

	if((fp = fopen(path, "r")) == NULL) {
		fprintf(stderr, "fopen error in calcul_stat\n");
		exit(1);
	}
	int i;
	for(i = 0; i < 18; i++)
		fgets(tmp, sizeof(tmp), fp);
	fgets(tmp, sizeof(tmp), fp);

	if(!strncmp(tmp, "VmLck", 5)) {
		char tmptmp[10] = {0, };
		int j, k = 0;
		int res = 0;
		for(j = 0; j < strlen(tmp); j++) {
			if('0' <= tmp[j] && tmp[j] <= '9')
				tmptmp[k++] = tmp[j];
		}
		res = atoi(tmptmp);
		if(res)
			strcat(stat_sav, "L");
	}

	if(value_stat[1] == value_stat[6])
		strcat(stat_sav, "s");

	if(value_stat[20] > 1)
		strcat(stat_sav, "l");

	//pid_t console_pid = value_stat[6];
	pid_t my_pid = value_stat[8];
	//printf("%d %d\n", console_pid, my_pid);
	if(my_pid == getpgid(value_stat[1]))
		strcat(stat_sav, "+");

	fclose(fp);
	return;
}

void calcul_systime(ll value_stat[]) { //프로세스가 CPU를 사용한 총 시간 계산
	int ttime = (value_stat[14] + value_stat[15]) / sysconf(_SC_CLK_TCK);
	sprintf(systime_sav, "%2d", ttime / 60);
	sprintf(systime_sav+2, ":");
	sprintf(systime_sav+3, "%02d", ttime % 60);
	return;
}

void calcul_stime(ll value_stat[]) { //프로세스가 시작된 시간 확인
	char tstring[6] = {0, };
	memset(tstring, 0, sizeof(tstring));

	time_t t = time(NULL); //현재시간
	double utime = calcul_uptime();
	t -= utime; // t에 부팅시간 저장
	double ttime = (value_stat[22]) / sysconf(_SC_CLK_TCK);
	t += ttime;
	struct tm *ts = localtime(&t);
	
	sprintf(tstring, "%02d", ts->tm_hour);
	sprintf(tstring+2, ":");
	sprintf(tstring+3, "%02d", ts->tm_min);
	strcpy(stime_sav, tstring);
	return;
}

double calcul_mem(int fname) { //메모리 사용률 계산
	FILE *fp;
	char arr[NAS] = {0, };
	memset(arr, 0, sizeof(arr));
	int i, j = 0;
	int total = 0;
	double rss = calcul_rss(fname);
	double res;

	if((fp = fopen("/proc/meminfo", "r")) == NULL) {
		fprintf(stderr, "fopen error calcul_mem\n");
		exit(1);
	}
	fgets(arr, sizeof(arr), fp); //총 메모리 읽어옴
	for(i = 0; i < strlen(arr); i++)
		if('0' <= arr[i] && arr[i] <= '9')
			arr[j++] = arr[i];
	total = atoi(arr);
	res = ((double)rss / (double)total) * 100;

	fclose(fp);
	return res;
}

int calcul_rss(int fname) { //프로세스의 실제 메모리 계산
	char path[NAS] = "/proc/";
	char tmp[NAS] = {0, };
	char tmptmp[1024] = {0, };
	FILE *fp;
	int i, j = 0;
	int res;

	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%d", fname);
	strcat(path, tmp);
	memset(tmp, 0, sizeof(tmp));
	strcpy(tmp, path);
	strcat(tmp, "/status");

	if((fp = fopen(tmp, "r")) == NULL) {
		fprintf(stderr, "fopen error in calcul_rss\n");
		return 0;
	} //proc/pid/status 열기

	for(i = 1; i < 22; i++)
		fgets(tmptmp, sizeof(tmptmp), fp);
	
	memset(tmptmp, 0, sizeof(tmptmp));
	fgets(tmptmp, sizeof(tmptmp), fp); //vmRSS:   xxxxKB
	for(i = 0; i < strlen(tmptmp); i++)
		if('0' <= tmptmp[i] && tmptmp[i] <= '9')
			tmptmp[j++] = tmptmp[i]; 

	res = atoi(tmptmp);

	fclose(fp);
	return res;
}

double calcul_cpu(ll value_stat[]) { //cpu사용률 계산
	double sstime = calcul_uptime() - (value_stat[22] / sysconf(_SC_CLK_TCK));
	double per = (value_stat[14] + value_stat[15]) / sysconf(_SC_CLK_TCK) / sstime * 100;
	return per;
}

double calcul_uptime(void) { //부팅 이후 흐른 시간 계산
	FILE *fp;
	double time;
	if((fp = fopen("/proc/uptime", "r")) == NULL) {
		fprintf(stderr, "fopen error in calcul_uptime\n");
		exit(1);
	}
	fscanf(fp, "%lf", &time);
	fclose(fp);
	return time;
}
