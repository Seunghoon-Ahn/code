#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <termio.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <ctype.h>
#include <utmp.h>
#define NAS 100

typedef long long ll;

typedef struct {
	int pid;  //process id
	char user[20]; //user name
	int pr, ni;
	int virt, res, shr; // virtual real share memory size
	char status[3]; //STAT
	double cpu; //cpu usage percentage
	double mem; //memory usage percentage
	time_t time; //cpu usage time
	char command[100]; //process name
}psset; //프로세스의 정보를 저장하기 위한 구조체

psset arr[102020];
int height; //terminal line size
int width;  //terminal horizonal width
int ps_num; //total process number
int run_ps; //number of running process
int sleep_ps; //number of sleeping process
int stop_ps; //number of stop process
int zom_ps; //number of zombie process
int start = 0; //initial location of process list
char user_sav[10]; //glo_val for user name
long long old_cpu[9]; //array for saving past cpu info

void calcul_sz(void);
void get_data(void);
void print_head(void);
void print_data(int st);
int getch(void);
int get_input(void);
void calcul_user(int fname);
double calcul_cpu(ll value_stat[]);
double calcul_mem(int fname);
int calcul_rss(int fname);
int calcul_shr(int fname);
double calcul_uptime(void);
void calcul_user(int fname);
int calcul_systime(ll value_stat[]);
psset read_info(int fname);
void my_func_handler(int signo);
static int f_function(const struct dirent *dir);
int cmp(const struct dirent **a, const struct dirent **b);

void my_func_handler(int signo) { //signal handler function for SIGALRM
	calcul_sz();
	get_data();
	print_data(start);
	alarm(3);
}

int main(int argc, char *argv[]) {
	calcul_sz(); //get terminal size (width, height)
	get_data(); //get data of processes
	print_data(start); //initial print of total infomation and frame

	signal(SIGALRM, my_func_handler); //set SIGALRM signal handler function
	while(1) {
		alarm(3);
		int input = get_input(); //get input from user

		if(input == 1) //input = 'q'
			break; //quit ttop process
		else if (input == 2) { //input = 'up arrow key'
			start--;
			if(start < 0)
				start = 0;
			calcul_sz();
			get_data();
			print_data(start);
		}
		else if (input == 3) { //input = 'down arrow key'
			start++;
			calcul_sz();
			get_data();
			print_data(start);
		}
		else //input = other else
			continue;
	}
	return 0;
}

void calcul_sz(void) { //get terminal size
	struct winsize sz;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &sz);
	width = sz.ws_col + 1;
	height = sz.ws_row - 8; //save the terminal size in glo_value
	return;
}

int get_input(void) { //get input from user
	int sum = 0;
	char input1 = getch();
	sum += input1;
	if(input1 == 'q')
		return 1; //q
	else {
		char input2 = getch();
		sum += input2;
		input2 = getch();
		sum += input2;
	}

	if(sum == 183)
		return 2; //위 화살표
	else if (sum == 184)
		return 3; //아래 화살표
	else
		return 4; //그 외
}

void get_data(void) { //get process list from /proc directory
	memset(arr, 0, sizeof(arr));
	struct dirent **namelist;
	int count;
	int idx;
	char path[100] = "/proc";

	if((count = scandir(path, &namelist, f_function, cmp)) == -1) {
		fprintf(stderr, "scandir error!\n");
		return;
	} //use scandir function for get list of process
	ps_num = count;
	int i;
	run_ps = sleep_ps = zom_ps = stop_ps = 0; //initialize the number of process
	for(i = 0; i < count; i++) {
		int fname = atoi(namelist[i]->d_name);
		if(fname <= 0)
			continue;
		arr[i] = read_info(fname); //read infomation from proc/[pid] directory
	}

	for(i = 0; i < count; i++)
		free(namelist[i]);
	free(namelist); //free allocated memory

	return;
}

static int f_function(const struct dirent *dir) { //filter function for scandir
	if(isdigit(dir->d_name[0]))
		return 1;
	else
		return 0;
}

int cmp(const struct dirent **a, const struct dirent **b) { //sort function for scandir
	int x = atoi((*a)->d_name);
	int y = atoi((*b)->d_name);
	return x > y;
}

void print_head(void) { //ttop의 앞부분을 출력하는 함수
	int utime = calcul_uptime(); //현재까지의 uptime을 얻어옴
	long long cur_cpu[9] = {0, };
	double res_cpu[8] = {0, }; 
	double la1, la2, la3;
	time_t curtime = time(NULL);
	struct tm *t = localtime(&curtime); //현재시간을 얻어옴
	struct dirent **namelist;
	char tmp[100];
	int mem[4] = {0, };
	int swapm[4] = {0, };
	char make_num[20] = {0, };
	char output[1000] = {0, };
	int sum = 0;
	int i, j;
	struct utmp *myutmp;
	FILE *fp;
	int count = 0; //user 수

	setutent();
	while((myutmp = getutent()) != NULL) {
		if(myutmp->ut_type == USER_PROCESS)
			count++;
	}
	endutent();

	if((fp = fopen("/proc/loadavg", "r")) == NULL) {
		fprintf(stderr, "fopen error in print_head\n");
		return;
	} //loadaverage 정보를 읽어옴
	fscanf(fp, "%lf%lf%lf", &la1, &la2, &la3);
	fclose(fp);

	if((fp = fopen("/proc/stat", "r")) == NULL) {
		fprintf(stderr, "fopen error2 in print_head\n");
		return;
	} //2번째줄의 CPU 사용률 정보를 가져옴
	fscanf(fp, "%s", tmp);
	for(i = 0; i < 8; i++) {
		fscanf(fp, "%lld", &cur_cpu[i]);
		sum += cur_cpu[i];
	}
	cur_cpu[8] = sum;
	for(i = 0; i < 8; i++) {
		res_cpu[i] = (double)(cur_cpu[i] - old_cpu[i]) / (double)(cur_cpu[8] - old_cpu[8]) * 100;
	}
	memcpy(old_cpu, cur_cpu, sizeof(old_cpu));
	fclose(fp);

	if((fp = fopen("/proc/meminfo", "r")) == NULL) {
		fprintf(stderr, "fopen error3 in print_head\n");
		return;
	} //메모리 사용량 정보를 가져옴
	memset(tmp, 0, sizeof(tmp));
	memset(make_num, 0, sizeof(make_num));
	fgets(tmp, sizeof(tmp), fp);
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	mem[0] = atoi(make_num); // 전체 메모리

	memset(tmp, 0, sizeof(tmp));
	memset(make_num, 0, sizeof(make_num));
	fgets(tmp, sizeof(tmp), fp);
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	mem[1] = atoi(make_num); // free 메모리

	memset(tmp, 0, sizeof(tmp));
	memset(make_num, 0, sizeof(make_num));
	fgets(tmp, sizeof(tmp), fp);
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	swapm[3] = atoi(make_num); // avail 메모리

	memset(tmp, 0, sizeof(tmp));
	memset(make_num, 0, sizeof(make_num));
	fgets(tmp, sizeof(tmp), fp);
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	mem[3] += atoi(make_num); // buffers 메모리

	memset(tmp, 0, sizeof(tmp));
	memset(make_num, 0, sizeof(make_num));
	fgets(tmp, sizeof(tmp), fp);
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	mem[3] += atoi(make_num); // cache 메모리

	for(i = 0; i < 10; i++) {
		memset(tmp, 0, sizeof(tmp));
		fgets(tmp, sizeof(tmp), fp);
	}
	memset(make_num, 0, sizeof(make_num));
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	swapm[0] = atoi(make_num); // Swap total 메모리

	memset(tmp, 0, sizeof(tmp));
	memset(make_num, 0, sizeof(make_num));
	fgets(tmp, sizeof(tmp), fp);
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	swapm[1] = atoi(make_num); // Swap free 메모리

	for(i = 0; i < 8; i++) {
		memset(tmp, 0, sizeof(tmp));
		fgets(tmp, sizeof(tmp), fp);
	}
	memset(make_num, 0, sizeof(make_num));
	j = 0;
	for(i = 0; i < strlen(tmp); i++)
		if(isdigit(tmp[i]))
			make_num[j++] = tmp[i];
	mem[3] += atoi(make_num); // SReclaimable 메모리

	mem[2] = mem[0] - mem[1] - mem[3];
	swapm[2] = swapm[0] - swapm[1];

	write(1, "\33[3J\33[H\33[2J", 11); //화면 초기화

	memset(output, 0, sizeof(output));

	snprintf(output, width, "top - %02d:%02d:%02d up %2d:%02d, %2d user,  load average: %.2lf, %.2lf, %.2lf", 
		t->tm_hour, t->tm_min, t->tm_sec, utime/3600, (utime%3600)/60, count, la1, la2, la3);
	printf("%s\n", output);
	memset(output, 0, sizeof(output));

	snprintf(output, width, "Tasks:%4d total,%4d running,%4d sleeping,%4d stopped,%4d zombie", 
		ps_num, run_ps, sleep_ps, stop_ps, zom_ps);
	printf("%s\n", output);
	memset(output, 0, sizeof(output));

	snprintf(output, width, "%%Cpu(s):%5.1lf us,%5.1lf sy,%5.1lf ni,%5.1lf id,%5.1lf wa,%5.1lf hi,%5.1lf si,%5.1lf st", 
		res_cpu[0], res_cpu[2], res_cpu[1], res_cpu[3], res_cpu[4], res_cpu[5], res_cpu[6], res_cpu[7]);
	printf("%s\n", output);
	memset(output, 0, sizeof(output));

	snprintf(output, width, "KiB Mem :%9d total,%9d free,%9d used,%9d buff/cache", mem[0], mem[1], mem[2], mem[3]);
	printf("%s\n", output);
	memset(output, 0, sizeof(output));
	
	snprintf(output, width, "KiB Swap:%9d total,%9d free,%9d used,%9d avail Mem", swapm[0], swapm[1], swapm[2], swapm[3]);
	printf("%s\n", output);
	//헤드 부분 출력단
	fclose(fp);
	return;
}

void print_data(int st) { //프로세스의 정보를 출력하는 함수
	print_head(); //헤더 출력
	printf("\n   PID USER      PR  NI    VIRT    RES    SHR S  %%CPU %%MEM     TIME+ COMMAND\n");
	char str[1024];
	memset(str, 0, sizeof(str));
	for(int i = st; i < st + height; i++) {
		memset(str, 0, sizeof(str));
		if(arr[i].pid == 0)
			;
		else if(arr[i].pr != -100) {
			snprintf(str, width, "%6d %-8s %3d %3d %7d %6d %6d %-2s %4.1lf %4.1lf %3ld:%02ld.%02ld %s", 
				arr[i].pid, arr[i].user, arr[i].pr, arr[i].ni, arr[i].virt, arr[i].res, arr[i].shr, arr[i].status, arr[i].cpu,
				arr[i].mem, arr[i].time / 6000, (arr[i].time % 6000)/100, (arr[i].time % 6000) % 100, arr[i].command);
		}
		else {
			snprintf(str, width, "%6d %-8s  rt %3d %7d %6d %6d %-2s %4.1lf %4.1lf %3ld:%02ld.%02ld %s", 
				arr[i].pid, arr[i].user, arr[i].ni, arr[i].virt, arr[i].res, arr[i].shr, arr[i].status, arr[i].cpu,
				arr[i].mem, arr[i].time / 6000, (arr[i].time % 6000)/100, (arr[i].time % 6000) % 100, arr[i].command);
		}
		printf("%s\n", str);
	} //화면의 높이 만큼 출력
	return;
}

psset read_info(int fname) { //프로세의 정보를 읽어오는 함수
	char path[50] = "/proc/";
	char tmp[150] = {0, };
	char tmptmp[100] = {0, };
	char tmptmptmp[100] = {0, };
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
	} ///proc/pid/stat 열기

	fscanf(fp, "%lld", &value_stat[1]); //pid
	fscanf(fp, "%s", tmp); //이름
	memset(pcs.status, 0, sizeof(pcs.status));
	fscanf(fp, "%s", pcs.status); //3번쨰에 있는 status 문자를 구조체에 집어넣음

	if(!strcmp(pcs.status, "R"))
		run_ps++;
	else if (!strcmp(pcs.status, "S"))
		sleep_ps++;
	else if (!strcmp(pcs.status, "T") || !strcmp(pcs.status, "t"))
		stop_ps++;
	else if (!strcmp(pcs.status, "Z"))
		zom_ps++;
	//프로세스의 상태를 보고 갯수를 셈
	for(i = 4; i <= 52; i++)
		fscanf(fp, "%lld", &value_stat[i]);
	//stat 파일 읽어왔음
	fclose(fp);

	memset(tmp, 0, sizeof(tmp));
	strcpy(tmp, path);
	strcat(tmp, "/comm");
	if((fp =fopen(tmp, "r")) == NULL) {
		fprintf(stderr, "fopen error2 in read_info\n");
		exit(1);
	} //comm 열어서 command 확인

	fgets(tmptmp, sizeof(tmptmp), fp);
	tmptmp[strlen(tmptmp)-1] = '\0';
	strcpy(pcs.command, tmptmp);

	calcul_user(fname);
	strcpy(pcs.user, user_sav);
	memset(user_sav, 0, sizeof(user_sav));

	pcs.cpu = calcul_cpu(value_stat);
	pcs.mem = calcul_mem(fname);
	pcs.virt = value_stat[23] / 1024;
	pcs.res = calcul_rss(fname);
	pcs.shr = calcul_shr(fname);
	pcs.pr = value_stat[18];
	pcs.ni = value_stat[19];
	pcs.time = calcul_systime(value_stat);

	fclose(fp);
	return pcs;
}

int calcul_shr(int fname) { //가상메모리의 크기를 계산하는 함수
	char path[NAS] = "/proc/";
	char tmp[NAS] = {0, };
	char tmptmp[1024] = {0, };
	char tmptmptmp[100] = {0, };
	FILE *fp;
	int i, j = 0;
	int res = 0;

	memset(tmptmptmp, 0, sizeof(tmptmptmp));
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

	for(i = 1; i < 25; i++)
		fgets(tmptmp, sizeof(tmptmp), fp);
	
	if(strncmp(tmptmp, "RssFile", 7)) {
		fclose(fp);
		return 0;
	}

	for(i = 0; i < strlen(tmptmp); i++)
		if(isdigit(tmptmp[i]))
			tmptmptmp[j++] = tmptmp[i]; 

	res += atoi(tmptmptmp);


	memset(tmptmp, 0, sizeof(tmptmp));
	memset(tmptmptmp,0, sizeof(tmptmptmp));
	fgets(tmptmp, sizeof(tmptmp), fp); //RssShmem:   xxxxKB

	if(strncmp(tmptmp, "RssShmem", 8)) {
		fclose(fp);
		return 0;
	}
	j = 0;
	for(i = 0; i < strlen(tmptmp); i++)
		if(isdigit(tmptmp[i]))
			tmptmptmp[j++] = tmptmp[i]; 

	res += atoi(tmptmptmp);

	fclose(fp);
	return res;
}


int calcul_systime(ll value_stat[]) { //프로세스의 CPU점유 시간 계산
	int ttime = (value_stat[14] + value_stat[15]) / sysconf(_SC_CLK_TCK);
	return ttime;
}

double calcul_mem(int fname) { // 프로세스의 메모리 점유율 계산
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
		if(isdigit(arr[i]))
			arr[j++] = arr[i];
	total = atoi(arr);
	res = ((double)rss / (double)total) * 100;

	fclose(fp);
	return res;
}

int calcul_rss(int fname) { //프로세스의 실졔메모리 계산
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

	if(strncmp(tmptmp, "VmRSS", 5)) {
		fclose(fp);
		return 0;
	}

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

void calcul_user(int fname) { // 유저이름을 추출하는 함수
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
	//유저 아이디로 유저의 이름을 추출함
	if(strlen(p->pw_name) > 8) {
		strncpy(user_sav, p->pw_name, 7);
		strcat(user_sav, "+");
	}
	else
		strcpy(user_sav, p->pw_name);

	fclose(fp);
	return;
}

int getch(void){ //키 입력후 즉각적인 반응을 위한 함수
	int ch;
	struct termios buf, save;
	tcgetattr(0,&save);
	buf = save;
	buf.c_lflag &= ~ICANON;
	buf.c_lflag &= ~ECHO;
	//buf.c_cc[VMIN] = 1;
	//buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}