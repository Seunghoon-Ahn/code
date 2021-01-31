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
#include <sys/time.h>
#include <termios.h>

#define SECOND_TO_MICRO 1000000 // 1초는 백만마이크로초
#define BUF_LEN 200

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);
//프로그램 실행 시간 측정함수
void print_usage(void); //도움말을 출력하는 함수
void make_daemon(void); //디몬 프로세스를 호출하기 위한 함수 -> ssu_daemon.c에 존재
void tree_making(char path[]); //트리를 그리기 위한 함수
void size_check(char input[]); //size를 체크하는 함수
int dsize_check(char name[]); //디렉토리의 size를 체크하기 위한 함수
void f_delete(char input[]); //delete 명령어를 처리하는 함수
void delete_timer(int signo); //delete를 위한 alarm을 받는 핸들러 함수
int is_delete(void); //delete에 -r 옵션일때 정말로 삭제할 것인지를 묻는 함수
void make_delete(void); // delete시에 파일 이름을 겹치지 않게 바꿔서 delete 하는 함수
int same_name_max(char fname[]); //원 이름이 같은 파일의 갯수를 세는 함수
int dir_skip(const struct dirent *info); //scandir의 filter 함수
void make_info(char fname[]); //delete 시에 info 파일을 만드는 함수
void find_2kb(void); //info 폴더가 2KB를 넘는지 확인하는 함수
void find_oldest(void); //info 폴더에서 가장 오래된 파일을 찾아 삭제하는 함수
void f_recover(char input[]); //recover 명령어를 진행하는 함수
int same_name_max2(char fname[], char last_locdir[]);
//recover 시에 복원될 폴더에 같은 이름을 가진 파일이 있는지 확인하는 함수

char *prompt[] = {"delete", "size", "recover", "tree", "exit", "help"};

bool doing_alarm = false;
bool check[6] = {0, 0, 0, 0, 0, 0};
int checksum = 0;
int daemon_pid;
char fname_delete[BUF_LEN];
char option_delete[3];
char current_wd[BUF_LEN];

int main(void) {
	struct timeval begin_t, end_t;
	gettimeofday(&begin_t, NULL);

  char input[BUF_LEN]; //입력받은 문장 전체
  char const_input[BUF_LEN];
  char todo[10]; //명령어 분리
  memset(input, 0, sizeof(input));
  //디몬 부르기
  make_daemon();


  //trash 폴더가 없는 경우 만들기
  if(access("./trash", F_OK) == -1)
  	mkdir("./trash", 0777);
  if(access("./trash/files", F_OK) == -1)
  	mkdir("./trash/files", 0777);
  if(access("./trash/info", F_OK) == -1)
  	mkdir("./trash/info", 0777);

	getcwd(current_wd, BUF_LEN); //현재 작업디렉토리 저장
	while(1) {
		chdir(current_wd);

		memset(input, 0, sizeof(input));
		memset(const_input, 0, sizeof(const_input));

		printf("20162481>");
		fgets(input, BUF_LEN, stdin);
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
	} //입력된 명령어와 지정된 명령어를 비교함

	if(checksum == 0) { //명령어가 올바르지 않은 경우 도움말 출력
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
	else if (check[3] == true) //tree 일때
		tree_making("./check");
	else if (check[4] == true) { //exit 일때
	  //int id = getpid();
	  //kill(id+2, SIGKILL);
		printf("Exiting......\n");
		gettimeofday(&end_t, NULL);
		ssu_runtime(&begin_t, &end_t);
		exit(0);
	}
	else if (check[5] == true) //help일때
		print_usage();
}

return 0;
}

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t)
{ 
  end_t->tv_sec -= begin_t->tv_sec; //끝난 시간에서 처음시간을 뺌

  if(end_t->tv_usec < begin_t->tv_usec){
  	end_t->tv_sec--;
  	end_t->tv_usec += SECOND_TO_MICRO;
  } //나중의 us값이 작을경우 1초를 뺴서 us값이 더해줌

  end_t->tv_usec -= begin_t->tv_usec;
  printf("Runtime: %ld:%02ld:%06ld(min:sec:usec)\n",
  	end_t->tv_sec / 60, end_t->tv_sec % 60, end_t->tv_usec);
} //프로그램 수행시간을 분, 초, 마이크로초로 출력

//cwd = check 바깥
void f_recover(char input[]) { //recover하는 함수
	char info_path[BUF_LEN] = "./trash/info/";
	char file_path[BUF_LEN] = "./trash/files/";
  char fname[BUF_LEN]; // 원래의 이름
  char dest[BUF_LEN];
  char *ptr = input;
  int count;
  struct dirent **namelist1;
  struct dirent **namelist2;
  char f_name[BUF_LEN]; //현재 trash 폴더 안의 이름
  char buf[BUF_LEN];
  char buf_D[BUF_LEN];
  char buf_M[BUF_LEN];
  char last_locdir[BUF_LEN];
  int pfx, cnt = 0;
  int choose, check;
  int idc = 0, frontnum;
  char tmp[BUF_LEN];
  FILE *fp;

  memset(fname, 0, sizeof(fname));
  memset(dest, 0, sizeof(dest));
  memset(f_name, 0, sizeof(f_name));
  memset(buf, 0, sizeof(buf));
  memset(buf_D, 0, sizeof(buf_D));
  memset(buf_M, 0, sizeof(buf_M));
  memset(last_locdir, 0, sizeof(last_locdir));

  strcpy(fname, ptr+8); //명령어를 제외하고 파일 이름만 받아들임
  //printf("%s\n", fname);
  if(fname[strlen(fname) - 1] == '\n')
  	fname[strlen(fname) - 1] = '\0';

  if((count = scandir("./trash/info", &namelist1, dir_skip, alphasort)) == -1) {
  	fprintf(stderr, "scandir error in f_recover function\n");
  	return;
  }
  check = 0;
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
  		check = 1;
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
	} //사용자가 입력한 파일이름과 이름이 같은 파일을 모두 출력해줌

}

if(check == 0) {
	printf("There is no '%s' in 'trash' directory!\n", fname);
	return;
  } //이름이 같은 파일이 없는 경우 에러 출력 후 리턴

  printf("Choose : ");
  scanf("%d", &choose);
  getchar();
  //사용자가 어떤 파일을 복구 할 것인지 확인함
  //숫자 + _ + 파일 이름 해서 info 파일 열어서 파일 원래 위치 확인
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
  if(buf[strlen(buf) - 1] == '\n')
  	buf[strlen(buf) - 1] = '\0';


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
	sprintf(tmp, "/%d_%s", frontnum, fname); //앞에 숫자 붙여서 rename함
	strcat(last_locdir, tmp);
	strcat(file_path, f_name);
	rename(file_path, last_locdir);
	strcat(info_path, f_name);
	remove(info_path); //info파일 지움
	return;
}

}

int same_name_max2(char fname[], char last_locdir[]) { //과거의 폴더에서 같은 이름 파일의 숫자의 최댓값을 계산해주는 함수
	struct dirent **namelist;
	int count, loc = 0;
	char tmp[BUF_LEN];
	int maxnum = 0;
	int num = 0;
	char *ptr = tmp;

	if((count = scandir(last_locdir, &namelist, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "last directory scan error in same_name_max2\n");
		return count;
	}

	for(int i = 0; i < count; i++) {
		ptr = tmp;
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp, namelist[i]->d_name);
		for(int j = 0; j < strlen(tmp); j++) {
			if(tmp[j] == '_') {
				loc = j;
				break;
	  } // 언더바의 위치를 찾아서 그 앞의 숫자를 제거할 수 있도록 함
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

for(int i = 0; i <count; i++)
	free(namelist[i]);
free(namelist);

  return maxnum; //같은 이름을 가진 파일이 없다면 0을 리턴함
}

void f_delete(char input[]) {
	char backup_input[BUF_LEN] = {0, };
  char fname[BUF_LEN] = {0, }; //파일 이름
  char *tmp;
  char rpath[BUF_LEN] = {0, }; // 파일 절대경로
  char d_day[BUF_LEN] = {0, }; // 삭제 날짜
  char d_time[BUF_LEN] = {0, }; //삭제 시간
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

  if(lstat(rpath, &statbuf) < 0) { //파일 명이 이상한거 일단 다 걸러짐
  	fprintf(stderr, "File is not exist!!\n");
  	chdir(current_wd);
  	return;
  } // 존재하지 않는 파일을 삭제하려 하는 경우 에러 출력 후 리턴
  //printf("hi : %s\n", rpath);
  //이 아래부터 파일 명은 멀쩡하다
  if(strlen(backup_input) == strlen(fname) + 1){
  	strcpy(fname_delete, rpath);
  	memset(option_delete, 0, sizeof(option_delete));
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

}

void delete_timer(int signo) { //타이머가 울리면 파일을 삭제 하는 함수

	char rpath[BUF_LEN] = {0,};
	char fname[BUF_LEN] = {0,};
	char *ptr = fname_delete;
	int option_i = 0;
	int option_r = 0;
	int loc;

	memset(rpath, 0, sizeof(rpath));
	memset(fname, 0, sizeof(fname));

	strcpy(rpath, fname_delete);
	for(int i = 0; i < strlen(fname_delete); i++)
		if(fname_delete[i] == '/')
			loc = i;
		strcpy(fname, ptr + loc + 1);


		if(!strncmp(option_delete, "-i", 2))
			option_i = 1;
		else if(!strncmp(option_delete, "-r", 2)) {
			option_r = 1;
		}

		if(option_r) {
	//삭제할껀지 묻는 함수
	//Y는 삭제, N은 취소하고 리턴
	if(is_delete() < 0) //사용자가 n 선택했으면 취소
		return;
}

if(option_i) {
	//바로 삭제
	struct stat statbuf;
	lstat(rpath, &statbuf);
	if(!S_ISDIR(statbuf.st_mode)) {
		remove(rpath);
		return;
	}
	else {
		printf("Failed to delete directory : '%s' isn't empty!\n", fname);
		return;
	}
}
else {
	make_delete();
}

return;
}

int dir_skip(const struct dirent *info) {
	if(!strcmp(info->d_name, ".") || !strcmp(info->d_name, ".."))
		return 0;
	else return 1;
} //scandir에서 현재 디렉토리와 상위 디럭토리를 제외하기 위한 함수

int same_name_max(char fname[]) { //trash 폴더에서 같은 이름 파일의 숫자의 최댓값을 계산해주는 함수
	struct dirent **namelist;
	int count, loc = 0;
	char tmp[BUF_LEN];
	int maxnum = 0;
	int num = 0;
	char *ptr = tmp;

	if((count = scandir("./trash/files", &namelist, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "trash directory scan error in same_name_max\n");
		return count;
	}

	for(int i = 0; i < count; i++) {
		ptr = tmp;
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

for(int i = 0; i <count; i++)
	free(namelist[i]);
free(namelist);

  return maxnum; //같은 이름을 가진 파일이 없다면 0을 리턴함
}

//현재 작업디렉토리는 check 바깥
void make_delete(void) {
  char fname[BUF_LEN]; //순수한 파일 이름
  char path_files[BUF_LEN] = "trash/files/";
  char rpath_files[BUF_LEN];
  int loc;
  char newfname[BUF_LEN];
  char newpath[BUF_LEN];

  memset(fname, 0, sizeof(fname));
  memset(newfname, 0, sizeof(newfname));
  memset(newpath, 0, sizeof(newpath));
  memset(rpath_files, 0, sizeof(rpath_files));

  realpath(path_files, rpath_files);

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

  make_info(newfname); // info 파일 만드는 함수 호출

  rename(fname_delete, newpath);

}

void make_info(char fname[]) {
	char file_info[BUF_LEN] = "./trash/info/";
	FILE *infp;
	struct stat statbuf;
	struct tm tM, tD;
	time_t M, D;

  strcat(file_info, fname); //info 파일을 만들 경로 + 파일 이름
  if((infp = fopen(file_info, "w+")) < 0) {
  	fprintf(stderr, "Fail making info file\n");
  	return;
  }

  if(lstat(fname_delete, &statbuf) < 0) {
  	fprintf(stderr, "lstat error in make_info\n");
  	return;
  }

  M = statbuf.st_mtime;
  D = time(NULL);

  localtime_r(&M, &tM);
  localtime_r(&D, &tD);
  //info 파일에 정보를 작성해줌
  fprintf(infp, "[Trash Info]\n");
  fprintf(infp, "%s\n", fname_delete);
  fprintf(infp, "D : %d-%02d-%02d %02d:%02d:%02d\n", tD.tm_year+1900, tD.tm_mon+1, 
  	tD.tm_mday, tD.tm_hour, tD.tm_min, tD.tm_sec);
  fprintf(infp, "M : %d-%02d-%02d %02d:%02d:%02d\n", tM.tm_year+1900, tM.tm_mon+1, 
  	tM.tm_mday, tM.tm_hour, tM.tm_min, tM.tm_sec);

  fclose(infp);

  find_2kb(); //info파일이 2KB가 넘은 경우 가장 오래된 것을 삭제하는 함수

}

void find_2kb(void) {
	char buf[BUF_LEN];
	memset(buf, 0, sizeof(buf));
	getcwd(buf, BUF_LEN);

	chdir(current_wd);
	char info_path[BUF_LEN] = "./trash/info";
	int size;
	char fname[BUF_LEN] = {0,};

	while(1) {
		size = dsize_check(info_path);

		if(size < 2048)
			break;
		else
	  find_oldest(); //2KB가 넘었으면, 가장 오래된 파일을 찾아서 삭제함

}
chdir(buf);
return;
}

void find_oldest(void) { //가장 오래된 info 파일을 찾는 함수
	char info_path[BUF_LEN] = "./trash/info";
	char buf[BUF_LEN];
	char fname_todelete[BUF_LEN];
	struct dirent **namelist;
	char *ptr;
	struct tm t;
	time_t oldest, file_time;
	int count;
	FILE *fp;
	char cwd[BUF_LEN];
	char filepath[BUF_LEN];
	char infopath[BUF_LEN];

	memset(filepath, 0, sizeof(filepath));
	memset(infopath, 0, sizeof(filepath));
	memset(buf, 0, sizeof(buf));
	memset(cwd, 0, sizeof(cwd));
	memset(fname_todelete, 0, sizeof(fname_todelete));
	getcwd(cwd, BUF_LEN);

	if((count = scandir(info_path, &namelist, dir_skip, NULL)) == -1) {
		fprintf(stderr, "scndir error in find_oldest\n");
		return;
	}
	chdir(info_path);
	for(int i = 0; i < count; i++) {
		if((fp = fopen(namelist[i]->d_name, "r")) < 0) {
			fprintf(stderr, "fopen error in find_oldest\n");
			return;
		}
	//info 파일의 적혀있는 딜리트 타임을 읽어서 비교함
		fgets(buf, BUF_LEN, fp);
		memset(buf, 0, sizeof(buf));
		fgets(buf, BUF_LEN, fp);
		memset(buf, 0, sizeof(buf));
	fgets(buf, BUF_LEN, fp); //buf에 삭제 시간 읽어옴

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
  //원 파일과 info 파일 모두를 삭제함
for(int i = 0; i <count; i++)
	free(namelist[i]);
free(namelist); 

return;

}

int is_delete(void) { //i옵션일떄 사용자에게 삭제할지를 묻는 함수
	char input;
	printf("Delete [y/n]? ");
	scanf("%c", &input);
	getchar();

	if(input == 'y')
		return 1;
	else
		return -1;
}

void size_check(char input[]) { //입력받은 파일 또는 디렉토리의 사이즈를 확인
	char name[BUF_LEN] = {0, };
	char rpath[BUF_LEN] = {0, };
	char *tmp;
	struct stat statbuf;
	int res = 0;
	int maxdepth = 1;

  tmp = strtok(input, " "); //명령어 끌어옴

  tmp = strtok(NULL, " "); //파일 명을 tmp에 저장함
  strcpy(name, tmp);

  if(strlen(input) > 5 + strlen(name)) {
	tmp = strtok(NULL, " "); //옵션 받아옴
	tmp = strtok(NULL, " ");
	maxdepth = atoi(tmp);
	printf("%d\n", maxdepth);
}

if(name[strlen(name) - 1] == '\n')
	name[strlen(name) - 1] = '\0';

if(lstat(name, &statbuf) < 0) {
	fprintf(stderr, "stat error in size_check\n");
	return;
}

if(S_ISREG(statbuf.st_mode)) {
	if(name[0] == '/' || name[0] == '.')
		printf("%ld     %s\n",statbuf.st_size, name);
	else
		printf("%ld    ./%s\n",statbuf.st_size, name);
  } //입력된 것이 파일일 경우 사이즈 출력

  else if(S_ISDIR(statbuf.st_mode)) {
  	res = dsize_check(name);
  	if(name[0] == '/' || name[0] == '.')
  		printf("%d      %s\n", res, name);
  	else
  		printf("%d    ./%s\n", res, name);
  } //디렉토리의 경우 재귀로 내부의 파일들의 합을 구함

  return;
}

int dsize_check(char name[]) { //디렉토리의 사이즈를 구하는 함수
	int res = 0;
	struct dirent **namelist;
	int count;

	struct stat statbuf;
	char buf[BUF_LEN];
	memset(buf, 0, sizeof(buf));
	getcwd(buf, BUF_LEN);

	if((count = scandir(name, &namelist, NULL, alphasort)) == -1) {
		fprintf(stderr, "%s directory scan error in dsize_check\n", name);
		return 0;
	}
	chdir(name);
	for(int i = 0; i < count; i++) {
		if((!strcmp(namelist[i]->d_name, ".")) || (!strcmp(namelist[i]->d_name, "..")))
			continue;
		if(lstat(namelist[i]->d_name, &statbuf) < 0) {
			fprintf(stderr, "stat error2\n");
			return 0;
		}
		if(!S_ISDIR(statbuf.st_mode)) {
			res += statbuf.st_size;
		}
		else
			res += dsize_check(namelist[i]->d_name);
  } //디렉토리 내부의 파일의 크기를 더하고, 디렉토리일 경우 재귀적으로 사이즈를 구해서 리턴함

  chdir(buf);

  for(int i = 0; i <count; i++)
  	free(namelist[i]);
  free(namelist);

  return res;
}

int depth = 0;

void tree_making(char path[]) { //tree를 그리는 함수
	struct dirent **namelist;
	int count;
	int idx;
	struct stat statbuf;

	if((count = scandir(path, &namelist, dir_skip, alphasort)) == -1) {
		fprintf(stderr, "%s directory scan error in tree_making\n", path);
		return;
	}

	if(depth == 0)
		printf("%s\n", path+2);

	chdir(path);
	for(int i = 0; i < count; i++) {
		struct stat statbuf;

		if((!strcmp(namelist[i]->d_name, ".")) || (!strcmp(namelist[i]->d_name, "..")))
			continue;

		if((lstat(namelist[i]->d_name, &statbuf)) < 0) {
			fprintf(stderr, "lstat error\n");
			return;
		}
		printf("┃\n");
		printf("┃");
		for(int i = 0; i < depth; i++) {
			printf("      ");
			if(i < depth-1)
				printf("┃");
		}
		for(int i = 0; i < depth; i++) {
			printf("┃\n");
		}
		if(depth != 0)
			printf("┃");

		for(int i = 0; i < depth; i++) {
			printf("      ");
			if(i < depth-1)
				printf("┃");
		}

		for(int i = 0; i <= depth; i++) {
			printf("━━━━");
		}

		printf(" %s\n", namelist[i]->d_name);
		if((statbuf.st_mode & S_IFDIR) == S_IFDIR) {
			depth++;
			tree_making(namelist[i]->d_name);
			depth--;
	} //파일일 경우 출력, 디렉토리일 경우 출력 후 재귀적이르도 디렉토리 내부 검색

}
chdir("..");

for(int i = 0; i <count; i++)
	free(namelist[i]);
free(namelist);

return;
}

void print_usage(void) //사용법 출력
{
	printf("Usage : ssu_mntr\n");
	printf(" delete <FILENAME> <END_TIME> <OPTION>\n");
	printf("   option :\n");
	printf("    -i        delete without moving file & info to 'trash'\n");
	printf("    -r        At end time, re-check about deleting file\n");
	printf(" size <FILENAME> <OPTION>\n");
	printf("   option : \n");
	printf("    -d <NUMBER> print <NUMBER> level(s) of sub directory\n");
	printf(" recover <FILENAME> <OPTION>\n");
	printf("   option :\n");
	printf("    -l          print file & info in 'trash' with time sequence before recover\n");
	printf(" tree           show 'check' directory structure with tree shape\n");
	printf(" exit           program exit & kill monitering background program\n");
	printf(" help           print usage\n");
}
