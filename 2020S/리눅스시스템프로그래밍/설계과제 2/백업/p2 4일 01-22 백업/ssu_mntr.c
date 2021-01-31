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


void print_usage(void);
void make_daemon(void);
void tree_making(char path[]);
void size_check(char buf[]);
int dsize_check(char name[]);

char *prompt[] = {"delete", "size", "recover", "tree", "exit", "help"};

bool check[6] = {0, 0, 0, 0, 0, 0};
int checksum = 0;
int daemon_pid;
/*
bool d_check = false;
bool s_check = false;
bool r_check = false;
bool t_check = false;
bool e_check = false;
bool h_check = false;
*/

int main(void) {
	char input[100]; //입력받은 문장 전체
	char const_input[100];
	char todo[10]; //명령어 분리
	memset(input, 0, sizeof(input));
	//디몬 부르기
	make_daemon();

	while(1) {
		printf("20162481>");
		fgets(input, 100, stdin);
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
			;
		else if (check[1] == true) {//size 일때
			size_check(const_input);
		}
		else if (check[2] == true) //recover일때
			;
		else if (check[3] == true) {//tree 일때
			tree_making("./check");
		}
		else if (check[4] == true) {//exit 일때
			//kill(daemon_pid, SIGKILL);
			exit(0);
		}
		else if (check[5] == true) //help일때
			print_usage();




		/*
		for(int i = 0; i < 6; i++)
			printf("%d ", check[i]);
		*/


		//printf("%s", todo);




	}

	return 0;
}

void size_check(char input[]) { //입력받은 파일 또는 디렉토리의 사이즈를 확인
	char name[100] = {0, };
	char *tmp;
	struct stat statbuf;
	int res = 0;

	tmp = strtok(input, " "); //명령어 끌어옴

	tmp = strtok(NULL, " "); //파일 명을 tmp에 저장함
	strcpy(name, tmp);

	if(name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1] = '\0';

	printf("%s\n", name); 

	if(stat(name, &statbuf) < 0) {
		fprintf(stderr, "stat error1\n");
		return;
	}

	if(S_ISREG(statbuf.st_mode))
		printf("%ld    	%s\n",statbuf.st_size, name);

	else if(S_ISDIR(statbuf.st_mode))
		res = dsize_check(name);

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
			printf("%ld    	%s\n", statbuf.st_size, namelist[i]->d_name);
		}
		else
			res += dsize_check(namelist[i]->d_name);

	}
	chdir("..");
	printf("%d    	%s\n", res, name);

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
