#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>

void print_usage(void);
void make_daemon(void);
void tree_making(char path[]);
void size_check(char input[]);
int dsize_check(char name[]);
void f_delete(char input[]);
void delete_timer(int signo);
int is_delete(void);
void make_delete(void);
//int same_name(char fname[]);
int same_name_max(char fname[]);
int dir_skip(const struct dirent *info);
void make_info(char fname[]);
void find_2kb(void);
void find_oldest(void);
void f_recover(char input[]);
int same_name_max2(char fname[], char last_locdir[]);

char *prompt[] = {"delete", "size", "recover", "tree", "exit", "help"};

bool check[6] = {0, 0, 0, 0, 0, 0};
int checksum = 0;
int daemon_pid;
char fname_delete[200];
char option_delete[3];
char current_wd[200];
/*
bool d_check = false;
bool s_check = false;
bool r_check = false;
bool t_check = false;
bool e_check = false;
bool h_check = false;
*/

int main(void) {
	char input[200]; //입력받은 문장 전체
	char const_input[200];
	char todo[10]; //명령어 분리
	memset(input, 0, sizeof(input));
	//디몬 부르기
	//make_daemon();

	//trash 폴더가 없는 경우 만들기
	if(access("./trash", F_OK) == -1)
		mkdir("./trash", 0777);
	if(access("./trash/files", F_OK) == -1)
		mkdir("./trash/files", 0777);
	if(access("./trash/info", F_OK) == -1)
		mkdir("./trash/info", 0777);

		getcwd(current_wd, 200);
	while(1) {
		chdir(current_wd);
		system("pwd");

		memset(input, 0, sizeof(input));
		memset(const_input, 0, sizeof(const_input));

		fflush(stdin);
		printf("20162481>");
		fgets(input, 200, stdin);
		fflush(stdin);
		strcpy(const_input, input);

		memset(check, 0, sizeof(check)); //check 배열 초기화
		checksum = 0;
		strcpy(todo, strtok(input, " "));

		if(!strcmp(todo, "\n")) //엔터만 입력되면 프롬프트 재출력
			continue;

		if(todo[strlen(todo) - 1] == '\n')
			todo[strlen(todo) - 1] = '\0'; //뒤에 있는 개행 문자 제거

		for(int i = 0; i < 6; i++) {
			if(!strcmp(todo, prompt[i])) {
				check[i] = true;
				checksum++;
			}
		}

		if(checksum == 0) {
			print_usage();
			continue;
		}


		if(check[0] == true) //delete일때
			f_delete(const_input);
		else if (check[1] == true) {//size 일때
			size_check(const_input);
		}
		else if (check[2] == true) //recover일때
			f_recover(const_input);
		else if (check[3] == true) {//tree 일때
			tree_making("./check");
		}
		else if (check[4] == true) {//exit 일때
			//int id = getpid();
			//kill(id+2, SIGKILL);
			exit(0);
		}
		else if (check[5] == true) //help일때
			print_usage();
	}

	return 0;
}

//cwd = check 바깥
void f_recover(char input[]) {
	char info_path[200] = "./trash/info/";
	char file_path[200] = "./trash/files/";
	char fname[100]; // 원래의 이름
	char dest[200];
	char *ptr = input;
	int count;
	struct dirent **namelist1;
	struct dirent **namelist2;
	char f_name[100]; //현재 trash 폴더 안의 이름
	char buf[200];
	char buf_D[100];
	char buf_M[100];
	char last_locdir[200];
	int pfx, cnt = 0;
	int choose;
	FILE *fp;

	memset(fname, 0, sizeof(fname));
	memset(dest, 0, sizeof(dest));
	memset(f_name, 0, sizeof(f_name));
	memset(buf, 0, sizeof(buf));
	memset(buf_D, 0, sizeof(buf_D));
	memset(buf_M, 0, sizeof(buf_M));
	memset(last_locdir, 0, sizeof(last_locdir));

	strcpy(fname, ptr+8);
	//printf("%s\n", fname);
	if(fname[strlen(fname) - 1] == '\n')
		fname[strlen(fname) - 1] = '\0';

	if((count = scandir("./trash/info", &namelist1, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "scandir error in f_recover function\n");
		return;
	}

	for(int i = 0; i < count; i++) {
		strcpy(buf, namelist1[i]->d_name);
		while(1) {
			if(buf[cnt] == '_')
				break;
			else
				cnt++;
		}
		ptr = buf;

		strcpy(f_name, ptr + cnt + 1);

		if(!strcmp(fname, f_name)) {
			memset(buf, 0, sizeof(buf));
			strcpy(buf, info_path);
			strcat(buf, namelist1[i]->d_name);
			if((fp = fopen(buf, "r")) < 0) {
				fprintf(stderr, "fopen error in recover function\n");
				return;
			}
			memset(buf, 0, sizeof(buf));
			fgets(buf, sizeof(buf), fp); //trash info 읽음
			memset(buf, 0, sizeof(buf));
			fgets(buf, sizeof(buf), fp); //원래 파일 경로 읽음
			memset(buf, 0, sizeof(buf));
			fgets(buf_D, sizeof(buf_D), fp); //삭제 시간 얻어옴	
			fgets(buf_M, sizeof(buf_M), fp); // 최종 수정 시간 얻어옴		
			if(buf_D[strlen(buf_D) - 1] == '\n')
				buf_D[strlen(buf_D) - 1] = '\0';
			if(buf_M[strlen(buf_M) - 1] == '\n')
				buf_M[strlen(buf_M) - 1] = '\0';
			//D M 출력 준비

			printf("%d. %s  %s %s\n", atoi(namelist1[i]->d_name), f_name, buf_D, buf_M);
			fclose(fp);
		}

	}

	printf("Choose : ");
	scanf("%d", &choose);
	fflush(stdin);

	//숫자+_+파일 이름 해서 info 파일 열어서 파일 원래 위치 확인
	// 그 디렉토리 읽어서 같은 이름 파일 있는 지 확인
	//없으면 앞에 숫자 띠고 가는거고 있으면 붙여서 가는거고
	memset(f_name, 0, sizeof(f_name));
	memset(buf, 0, sizeof(buf));

	sprintf(f_name, "%d_%s", choose, fname); //읽을 파일 확정
	strcpy(buf, info_path);
	strcat(buf, f_name); //info 파일의 위치 만듬

	if((fp = fopen(buf, "r")) < 0) {
		fprintf(stderr, "fopen error in recover function 2\n");
		return;
	}

	memset(buf, 0, sizeof(buf));
	fgets(buf, sizeof(buf), fp); //trash info 읽어서 버림
	memset(buf, 0, sizeof(buf));
	fgets(buf, sizeof(buf), fp); //파일의 경로 읽어옴

	cnt = 0;
	for(int i = 0; i < strlen(buf); i++) {
		if(buf[i] == '/')
			cnt = i;
	}

	strncpy(last_locdir, buf, cnt); //원래 파일이 있던 위치를 탐색
	
	if((count = scandir(last_locdir, &namelist2, dir_skip, alphasort)) < 0) {
		fprintf(stderr, "scandir error in recover function 2\n");
		return;
	}
	int idc = 0, frontnum;
	char tmp[100];
	ptr = tmp;
	for(int i = 0; i < count; i++) {
		//memset(tmp, 0, sizeof(tmp));
		//strcpy(tmp, namelist2->d_name);
		if(!strncmp(fname, namelist2[i]->d_name, strlen(namelist2[i]->d_name))) {
			idc = 1;
			break;
		}
	} //같은 이름 파일이 있으면 그만 찾고 break

	if(idc == 0) { //이름이 겹치는 파일이 없을떄
		strcat(file_path, f_name);
		rename(file_path, buf);
		strcat(info_path, f_name);
		remove(info_path);
		return;
	}
	else { //이름이 겹치는 파일이 있을때
		frontnum = same_name_max2(fname, last_locdir); //앞에 붙은 숫자 제일 큰거 구하기
		frontnum++;
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "/%d_%s", frontnum, fname);
		strcat(last_locdir, tmp);
		strcat(file_path, f_name);
		rename(file_path, last_locdir);
		strcat(info_path, f_name);
		remove(info_path);
		return;
	}

}

int same_name_max2(char fname[], char last_locdir[]) { //과거의 폴더에서 같은 이름 파일의 숫자의 최댓값을 계산해주는 함수
	struct dirent **namelist;
	int count, loc = 0;
	char tmp[100];
	int maxnum = 0;
	int num = 0;
	char *ptr = tmp;

	if((count = scandir(last_locdir, &namelist, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "last directory scan error in same_name_max2 function\n");
		return count;
	}

	for(int i = 0; i < count; i++) {
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, namelist[i]->d_name);
		for(int j = 0; j < strlen(tmp); j++) {
			if(tmp[j] == '_') {
				loc = j;
				break;
			}
		}
		if(loc != 0)
			ptr = ptr + loc + 1;
		 //이제 파일 이름만 남게 됨

		if(!strcmp(fname, ptr)) {
			num = atoi(namelist[i]->d_name); //1_1.c라면 num은 1이 될꺼임
			if(maxnum < num)
				maxnum = num; //앞에 붙은 값의 최대를 구함
		}
	}
	return maxnum; //같은 이름을 가진 파일이 없다면 0을 리턴함
}

void f_delete(char input[]) {
	char backup_input[200] = {0, };
	char fname[100] = {0, }; //파일 이름
	char *tmp;
	char rpath[200] = {0, }; // 파일 절대경로
	char d_day[100] = {0, }; // 삭제 날짜
	char d_time[100] = {0, }; //삭제 시간
	struct tm t;
	time_t deltime, curtime;
	int timegap = 0;
	char option[3]; //delete 할때의 옵션
	struct stat statbuf;
	struct stat stattmp;
	int t_checksum = 0;


	memset(backup_input, 0, sizeof(backup_input));
	memset(fname, 0, sizeof(fname));
	memset(rpath, 0, sizeof(rpath));
	memset(d_day, 0, sizeof(d_day));
	memset(d_time, 0, sizeof(d_time));
	memset(option, 0, sizeof(option));

	signal(SIGALRM, delete_timer);

	input = input+7;
	strcpy(backup_input, input); //명령어 잘라낸 인풋 배열 저장해둠
	chdir("./check");

	tmp = strtok(input, " ");
	if(tmp != NULL)
		strcpy(fname, tmp);
	if(fname[strlen(fname) - 1] == '\n') // 끝에 개행문자까지 포함된 경우 개행문자 삭제
		fname[strlen(fname) - 1] = '\0';
	realpath(fname, rpath);

	if(stat(rpath, &statbuf) < 0) { //파일 명이 이상한거 일단 다 걸러짐
		fprintf(stderr, "File is not exist!!\n");
		chdir(current_wd);
		return;
	} // 존재하지 않는 파일을 삭제하려 하는 경우 에러 출력 후 리턴
	//printf("hi : %s\n", rpath);
	//이 아래부터 파일 명은 멀쩡하다
	if(strlen(backup_input) == strlen(fname) + 1){
		strcpy(fname_delete, rpath);
		chdir(current_wd);
		delete_timer(SIGALRM);
		return;
	}
	else if((strlen(backup_input) > strlen(fname) + 1) && backup_input[strlen(fname) + 1] == '-') {
		tmp = strtok(NULL, " "); //-가 나온것은 시간이 입력되지 않았다는거
		strcpy(option, tmp);
		//printf("%s\n", option);
		strcpy(option_delete, option);
		strcpy(fname_delete, rpath);
		chdir(current_wd);
		delete_timer(SIGALRM);
		return;
	} //시간이 있을때
	else if((strlen(backup_input) > strlen(fname) + 1) && backup_input[strlen(fname) + 1] >= '0'
	 		&& backup_input[strlen(fname) + 1] <= '9'){
		tmp = strtok(NULL, "-"); //년도 커팅
		t.tm_year = atoi(tmp) - 1900;
		if(t.tm_year < 0)
			t_checksum++;
		tmp = strtok(NULL, "-"); //월 커팅
		t.tm_mon = atoi(tmp) - 1;
		if(t.tm_mon < 0)
			t_checksum++;
		tmp = strtok(NULL, " "); //일 커팅
		t.tm_mday = atoi(tmp);
		if(t.tm_mday < 1)
			t_checksum++;

		tmp = strtok(NULL, ":");
		t.tm_hour = atoi(tmp);
		if(t.tm_hour < 0)
			t_checksum++;
		tmp = strtok(NULL, " ");
		t.tm_min = atoi(tmp);
		if(t.tm_min < 0)
			t_checksum++;
		t.tm_sec = 0;

		if(t_checksum > 0) {
			fprintf(stderr, "Time input error!!\n");
			chdir(current_wd);
			return;
		}

		if((tmp = strtok(NULL, " ")) != NULL) {
			strcpy(option, tmp);
			strcpy(option_delete, option);
		}
		deltime = mktime(&t);
		curtime = time(NULL);
		//printf("%ld %ld\n", deltime, curtime);
		//현재시간, 삭제 시간 구함
		timegap = deltime - curtime;
		if(timegap < 0) {
			fprintf(stderr, "Delete time error!!\n");
			chdir(current_wd);
			return;
		}
		memset(fname_delete, 0, sizeof(fname_delete));
		memset(option_delete, 0, sizeof(option_delete));

		strcpy(fname_delete, rpath); //시그널 핸들러 함수에서 사용하기 위해 전역변수로 넘겨줌
		strcpy(option_delete, option);

		alarm(timegap);
		chdir(current_wd);
		return;
	}

	//chdir("..");
	
	//return;
}

void delete_timer(int signo) { //타이머가 울리면 파일을 삭제 하는 함수
	//printf("timer!!!\n");
	char rpath[200] = {0,};
	char fname[100] = {0,};
	int option_i = 0;
	int option_r = 0;

	memset(rpath, 0, sizeof(rpath));
	memset(fname, 0, sizeof(fname));

	strcpy(rpath, fname_delete);
	//strcpy() fname에 파일 이름만 골라서 저장하기
	//printf("tlqkf2");

	if(!strncmp(option_delete, "-i", 2))
		option_i = 1;
	else if(!strncmp(option_delete, "-r", 2)) {
		option_r = 1;
	}
	//printf("%s %d %d\n", rpath, option_i, option_r);
	if(option_r) {
		//삭제할껀지 묻는 함수
		//Y는 삭제, N은 취소하고 리턴
		if(is_delete() < 0) //사용자가 n 선택했으면 취소
			return;
	}
	//여기부터 진짜다
	if(option_i) {
		//바로 삭제
		remove(rpath);
		return;
	}
	else {
		//rename(rpath, ) 파일 trash로 옮기기
		make_delete();
	}

	return;
}

int dir_skip(const struct dirent *info) {
	if(!strcmp(info->d_name, ".") || !strcmp(info->d_name, ".."))
		return 0;
	else return 1;
} //scandir에서 현재 디렉토리와 상위 디럭토리를 제외하기 위한 함수
/*
int same_name(char fname[]) { //trash 폴더에서 같은 이름 파일의 갯수를 계산해주는 함수
	struct dirent **namelist;
	int count, loc = 0;
	char tmp[100];

	int num = 0;

	if((count = scandir("./trash/files", &namelist, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "trash directory scan error in same_name function\n");
		return count;
	}

	for(int i = 0; i < count; i++) {
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, namelist[i]->d_name);
		for(int j = 0; j < strlen(tmp); j++) {
			if(tmp[j] == '_') {
				loc = j;
				break;
			}
		}
		if(loc != 0)
			tmp = tmp + loc + 1;
		 //이제 파일 이름만 남게 됨

		if(!strcmp(fname, tmp)) //파일 이름이 겹치면 갯수 증가
			num++;
	}
	return num;
}
*/
int same_name_max(char fname[]) { //trash 폴더에서 같은 이름 파일의 숫자의 최댓값을 계산해주는 함수
	struct dirent **namelist;
	int count, loc = 0;
	char tmp[100];
	int maxnum = 0;
	int num = 0;
	char *ptr = tmp;

	if((count = scandir("./trash/files", &namelist, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "trash directory scan error in same_name function\n");
		return count;
	}

	for(int i = 0; i < count; i++) {
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, namelist[i]->d_name);
		for(int j = 0; j < strlen(tmp); j++) {
			if(tmp[j] == '_') {
				loc = j;
				break;
			}
		}
		if(loc != 0)
			ptr = ptr + loc + 1;
		 //이제 파일 이름만 남게 됨

		if(!strcmp(fname, ptr)) {
			num = atoi(namelist[i]->d_name); //1_1.c라면 num은 1이 될꺼임
			if(maxnum < num)
				maxnum = num; //앞에 붙은 값의 최대를 구함
		}
	}
	return maxnum; //같은 이름을 가진 파일이 없다면 0을 리턴함
}

//현재 작업디렉토리는 check 바깥
void make_delete(void) {
	char fname[100] = {0,};
	char path_files[100] = "trash/files/";
	char rpath_files[200] = "\0";
	//char path_info[100] = "./trash/info/";
	int loc;
	char newfname[100];
	char newpath[200];

	memset(fname, 0, sizeof(fname));
	memset(newfname, 0, sizeof(newfname));
	memset(newpath, 0, sizeof(newpath));
	memset(rpath_files, 0, sizeof(rpath_files));

	realpath(path_files, rpath_files);
	//printf("trash real path : %s\n", rpath_files);

	for(int i = 0; i < strlen(fname_delete); i++)
		if(fname_delete[i] == '/')
			loc = i;
	//마지막 슬래시의 위치를 가져옴, 그 다음부터 파일 이름이니까
	strcpy(fname, fname_delete+loc+1); //파일 이름만 건져오기

	int pfx = same_name_max(fname); //0이면 같은 이름을 가진 파일이 없다는것
	// 0 이상이라면 같은 이름을 가진 파일이 count개 있다는것	
	// count 보다 하나 큰 값으로 파일 앞에 붙이기
	pfx++; //pfx보다 1 큰값으로 앞에 붙여야됨

	//새 파일 이름 만들기
	sprintf(newfname, "/%d_%s", pfx, fname);

	strcpy(newpath, rpath_files);
	strcat(newpath, newfname);
	//trash/files로 보낼꺼 완성!

	//info파일 만드는 함수 만들어야됨
	make_info(newfname);	

	//fname_delete[strlen(fname_delete)] = '\0';
	//newpath[strlen(newpath)] = '\0';

	//printf("oldpath : %s1\n", fname_delete);
	//printf("newpath : %s1\n", newpath);

	rename(fname_delete, newpath);

}

void make_info(char fname[]) {
	char file_info[100] = "./trash/info/";
	FILE *infp;
	struct stat statbuf;
	struct tm tM, tD;
	time_t M, D;

	strcat(file_info, fname); //info 파일을 만들 경로 + 파일 이름
	if((infp = fopen(file_info, "w+")) < 0) {
		fprintf(stderr, "Fail making info file\n");
		return;
	}

	if(stat(fname_delete, &statbuf) < 0) {
		fprintf(stderr, "stat error in make_info\n");
		return;
	}

	M = statbuf.st_mtime;
	D = time(NULL);

	localtime_r(&M, &tM);
	localtime_r(&D, &tD);

	fprintf(infp, "[Trash Info]\n");
	fprintf(infp, "%s\n", fname_delete);
	fprintf(infp, "D : %d-%02d-%02d %02d:%02d:%02d\n", tD.tm_year+1900, tD.tm_mon+1, 
			tD.tm_mday, tD.tm_hour, tD.tm_min, tD.tm_sec);
	fprintf(infp, "M : %d-%02d-%02d %02d:%02d:%02d", tM.tm_year+1900, tM.tm_mon+1, 
			tM.tm_mday, tM.tm_hour, tM.tm_min, tM.tm_sec);

	fclose(infp);

	find_2kb();

}

void find_2kb(void) {
	chdir("..");
	char info_path[100] = "./trash/info";
	int size = dsize_check(info_path);
	char fname[100] = {0,};
	struct tm *t;
	time_t oldest;
	while(1) {
		size = dsize_check(info_path);
		chdir("..");
		if(size < 2048)
			break;
		else
			find_oldest();

	}
	chdir("./check");
	return;
}

void find_oldest(void) {
	char info_path[100] = "./trash/info";
	char buf[200];
	char fname_todelete[200];
	struct dirent **namelist;
	char *ptr;
	struct tm t;
	time_t oldest, file_time;
	int count;
	FILE *fp;
	char cwd[200];
	char filepath[200];
	char infopath[200];

	memset(filepath, 0, sizeof(filepath));
	memset(infopath, 0, sizeof(filepath));
	memset(buf, 0, sizeof(buf));
	memset(cwd, 0, sizeof(cwd));
	memset(fname_todelete, 0, sizeof(fname_todelete));
	getcwd(cwd, 200);

	if((count = scandir(info_path, &namelist, dir_skip, NULL)) == -1) {
		fprintf(stderr, "scndir error in find_oldest function\n");
		return;
	}
	chdir(info_path);
	for(int i = 0; i < count; i++) {
		if((fp = fopen(namelist[i]->d_name, "r")) < 0) {
			fprintf(stderr, "fopen error in find_oldest function!\n");
			return;
		}

		fgets(buf, 200, fp);
		memset(buf, 0, sizeof(buf));
		fgets(buf, 200, fp);
		memset(buf, 0, sizeof(buf));
		fgets(buf, 200, fp); //buf에 삭제 시간 읽어옴

		ptr = buf;
		ptr = ptr+5;

		t.tm_year = atoi(ptr) - 1900;
		t.tm_mon = atoi(ptr+5) - 1;
		t.tm_mday = atoi(ptr+8);
		t.tm_hour = atoi(ptr+11);
		t.tm_min = atoi(ptr+14);
		t.tm_sec = atoi(ptr+17);

		file_time = mktime(&t);

		if(i == 0) {
			oldest = file_time;
			strcpy(fname_todelete, namelist[i]->d_name);
		}
		else {
			if(oldest > file_time) {
				oldest = file_time;
				memset(fname_todelete, 0, sizeof(fname_todelete));
				strcpy(fname_todelete, namelist[i]->d_name);
			}
		}

	}
	chdir(cwd);

	strcpy(filepath, "./trash/files/");
	strcpy(infopath, "./trash/info/");
	strcat(filepath, fname_todelete);
	strcat(infopath, fname_todelete);

	remove(filepath);
	remove(infopath);

	return;

}




int is_delete(void) {
	char input;
	printf("Delete [y/n]? ");
	scanf("%c", &input);
	fflush(stdin);
	if(input == 'y')
		return 1;
	else
		return -1;
}




void size_check(char input[]) { //입력받은 파일 또는 디렉토리의 사이즈를 확인
	char name[100] = {0, };
	char rpath[200] = {0, };
	char *tmp;
	struct stat statbuf;
	int res = 0;

	tmp = strtok(input, " "); //명령어 끌어옴

	tmp = strtok(NULL, " "); //파일 명을 tmp에 저장함
	strcpy(name, tmp);

	if(name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1] = '\0';

	//printf("%s\n", name); 

	if(stat(name, &statbuf) < 0) {
		fprintf(stderr, "stat error1\n");
		return;
	}

	if(S_ISREG(statbuf.st_mode))
		printf("%ld    	./%s\n",statbuf.st_size, name);

	else if(S_ISDIR(statbuf.st_mode)) {
		res = dsize_check(name);
		printf("%d       ./%s\n", res, name);
	}

	return;
}

int dsize_check(char name[]) {
	int res = 0;
	struct dirent **namelist;
	int count;

	struct stat statbuf;

	if((count = scandir(name, &namelist, NULL, alphasort)) == -1) {
		fprintf(stderr, "%s directory scan error\n", name);
		return 0;
	}
	chdir(name);
	for(int i = 0; i < count; i++) {
		if((!strcmp(namelist[i]->d_name, ".")) || (!strcmp(namelist[i]->d_name, "..")))
			continue;
		if(stat(namelist[i]->d_name, &statbuf) < 0) {
			fprintf(stderr, "stat error2\n");
			return 0;
		}
		if(!S_ISDIR(statbuf.st_mode)) {
			res += statbuf.st_size;
			//printf("%ld    	%s\n", statbuf.st_size, namelist[i]->d_name);
		}
		else
			res += dsize_check(namelist[i]->d_name);

	}
	chdir("..");
	//printf("%d    	%s\n", res, name);

	return res;
}

int depth = 0;

void tree_making(char path[]) {
	struct dirent **namelist;
	int count;
	int idx;
	struct stat statbuf;
	//char real_path[2048];


	if((count = scandir(path, &namelist, NULL, alphasort)) == -1) {
		fprintf(stderr, "%s directory scan error\n", path);
		return;
	}

	if(depth == 0)
		printf("%s\n", path+2);

	chdir(path);
	for(int i = 0; i < count; i++) {
		struct stat statbuf;
		//memset(real_path, 0, sizeof(real_path));

		if((!strcmp(namelist[i]->d_name, ".")) || (!strcmp(namelist[i]->d_name, "..")))
			continue;

		//printf("%s\n", namelist[i]->d_name);

		//realpath(namelist[i]->d_name, real_path);
		//printf("%s\n", real_path);
		if((stat(namelist[i]->d_name, &statbuf)) < 0) {
			fprintf(stderr, "stat error\n");
			return;
		}
		printf("|\n");
		printf("|");
		for(int i = 0; i < depth; i++) {
			printf("    ");
			if(i < depth-1)
				printf("|");
		}
		for(int i = 0; i < depth; i++) {
			printf("|\n");
		}
		if(depth != 0)
			printf("|");

		for(int i = 0; i < depth; i++) {
			printf("    ");
			if(i < depth-1)
				printf("|");
		}

		for(int i = 0; i <= depth; i++) {
			printf("----");
		}

		printf("%s\n", namelist[i]->d_name);
		if((statbuf.st_mode & S_IFDIR) == S_IFDIR) {
			depth++;
			tree_making(namelist[i]->d_name);
			depth--;
		}

	}
	chdir("..");


	return;
}


void print_usage(void)
{
	printf("Usage : ssu_mntr\n");
	printf(" delete <FILENAME> <END_TIME> <OPTION>\n");
	printf("   option :\n");
	printf("	-i        delete without moving file & info to 'trash'\n");
	printf("	-r        At end time, re-check about deleting file\n");
	printf(" size <FILENAME> <OPTION>\n");
	printf("   option : \n");
	printf("	-d <NUMBER> print <NUMBER> level(s) of sub directory\n");
	printf(" recover <FILENAME> <OPTION>\n");
	printf("   option :\n");
	printf("	-l          print file & info in 'trash' with time sequence before recover\n");
	printf(" tree			show 'check' directory structure with tree shape\n");
	printf(" exit			program exit & kill monitering background program\n");
	printf(" help    		print usage\n");
}
