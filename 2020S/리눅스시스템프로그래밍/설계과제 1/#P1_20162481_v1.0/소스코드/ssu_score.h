#ifndef MAIN_H_
#define MAIN_H_

#ifndef true
	#define true 1
#endif
#ifndef false
	#define false 0
#endif
#ifndef STDOUT
	#define STDOUT 1
#endif
#ifndef STDERR
	#define STDERR 2
#endif
#ifndef TEXTFILE
	#define TEXTFILE 3
#endif
#ifndef CFILE
	#define CFILE 4
#endif
#ifndef OVER
	#define OVER 5
#endif
#ifndef WARNING
	#define WARNING -0.1
#endif
#ifndef ERROR
	#define ERROR 0
#endif

#define FILELEN 64
#define BUFLEN 1024
#define SNUM 100
#define QNUM 100
#define ARGNUM 5

struct ssu_scoreTable{
		char qname[FILELEN];
			double score;
}; //문제 번호와 그 문제의 배점을 저장하기 위한 구조체

void ssu_score(int argc, char *argv[]);
//main함수의 호출로 불러져 전체 채점을 시작하게 하는 함수, 
int check_option(int argc, char *argv[]);
//사용자로부터 인자로 받은 옵션을 확인하여 옵션에 알맞은 함수를 실행시키는 함수
void print_usage();
//-h 옵션 사용법 출력에 사용하는 함수
void score_students();
//학생들의 득점을 파일에 저장하고 총점을 계산하는 함수
double score_student(int fd, char *id);
//실질적으로 학생들의 점수를 계산하는 함수
void write_first_row(int fd);
//학생 배점 파일 첫줄에 문제 번호를 작성하는 함수
char *get_answer(int fd, char *result);
//학생 파일 또는 정답 파일에서 정답 텍스트만을 추출하는 함수
int score_blank(char *id, char *filename);
//빈칸문제를 채점하는 함수
double score_program(char *id, char *filename);
//프로그램 문제를 채점하는 함수
double compile_program(char *id, char *filename);
//학생 및 정답의 프로그램 문제를 컴파일하는 함수
int execute_program(char *id, char *filname);
// 컴파일된 프로그램 문제를 직접 실행시키는 함수
pid_t inBackground(char *name);
//백그라운드에서 실행중인 학생 또는 정답 프로그램의 프로세스 ID를 읽어옴
double check_error_warning(char *filename);
// 학생 프로그램의 에러 또는 경고의 개수를 계산하는 함수
int compare_resultfile(char *file1, char *file2);
//학생 프로그램의 결과물과 정답 프로그램의 결과물을 서로 비교하는 함수
void do_iOption(char (*ids)[FILELEN]);
//사용자가 i옵션을 입력했을 때, 입력받은 학생의 틀린 문제를 출력하는 함수
int is_exist(char (*src)[FILELEN], char *target);
// 학번을 바탕으로 존재하는 학생인지 판단하는 함수
int is_thread(char *qname);
//문제 번호를 바탕으로 –lpthread 옵션을 주고 컴파일해야하는 문제인지 확인하는 함수
void redirection(char *command, int newfd, int oldfd);
//파일 디스크립터를 다른 곳으로 옮겼다가 복구시키는 함수
int get_file_type(char *filename);
//파일이 텍스트 파일인지 소스코드인지 구분하는 함수
void rmdirs(const char *path);
//디렉터리를 삭제하는 함수
void to_lower_case(char *c);
// 모든 영문자를 소문자로 교체하는 함수
void set_scoreTable(char *ansDir);
//문제 배점 파일을 생성하는 함수
void read_scoreTable(char *path);
//문제 배점 파일을 읽어와 배열로 저장하는 함수
void make_scoreTable(char *ansDir);
//문제 배점 파일에 문제번호를 불러오는 함수
void write_scoreTable(char *filename);
//문제 배점 파일에 문제의 배점을 입력하고 저장하는 함수
void set_idTable(char *stuDir);
//학생들의 점수가 기록될 파일에 학생들의 학번을 입력하는 함수
int get_create_type();
//초기에 문제 배점 파일이 없는 경우 사용자로부터 문제의 배점을 입력받기 위한 함수
void sort_idTable(int size);
//학생들의 학번을 기준으로 학생 득점 파일에 학번을 작성하기 전 배열의 학번을 정렬하는 함수
void sort_scoreTable(int size);
//문제번호 순서대로 문제 배점 배열을 정렬하는 함수
void get_qname_number(char *qname, int *num1, int *num2);
//배열에서 문제 번호를 불러오는 함수
void do_mOption(void);
//m옵션을 실행하는 함수


#endif

