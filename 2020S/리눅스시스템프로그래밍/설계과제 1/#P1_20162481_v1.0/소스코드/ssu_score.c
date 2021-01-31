#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "ssu_score.h"
#include "blank.h"

extern struct ssu_scoreTable score_table[QNUM];
extern char id_table[SNUM][10];

struct ssu_scoreTable score_table[QNUM];
char id_table[SNUM][10];

char stuDir[BUFLEN]; //학생정답폴더의 디렉터리를 저장
char ansDir[BUFLEN]; //정답폴더의 디렉터리를 저장
char errorDir[BUFLEN]; //e옵션이 적용 되었을 때, 에러를 저장할 디렉터리 이름을 저장
char threadFiles[ARGNUM][FILELEN]; //t옵션 적용 시, -lpthread 옵션을 통해 컴파일 할 문제 번호를 저장함
char cIDs[ARGNUM][FILELEN]; //옵션의 조건으로 입력되는 데이터를 저장하기 위한 배열

int eOption = false;
int tOption = false;
int iOption = false;
int hOption = false;
int mOption = false;
//각 옵션들을 위한 스위치
void ssu_score(int argc, char *argv[])
{
    char saved_path[BUFLEN];
    int i, j, log;

    for(i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-h")){
            print_usage();
            return;
        }
    } // h옵션이 있을 경우 h옵션을 출력하고 프로그램 종료
    
    memset(saved_path, 0, BUFLEN); //saved_path배열 초기화
    if(argc >= 3 && (log = strcmp(argv[1], "-i")) != 0){
        strcpy(stuDir, argv[1]);
        strcpy(ansDir, argv[2]);
    } //옵션 i가 아닐경우 분리
    
    if(!check_option(argc, argv))
        exit(1);
    //입력된 옵션을 체크함
    j = 0;
    
    if(!eOption && !tOption && iOption && !log) {
        do_iOption(cIDs);
        return;
    } //i옵션만 활성화되어있고, 사용자가 문제 디렉터리를 입력하지 않았을 경우 
    //i옵션과 관련된 함수 실행

    getcwd(saved_path, BUFLEN);
    //현재 작업디렉터리의 경로를 얻어옴
    if(chdir(stuDir) < 0){
        fprintf(stderr, "%s doesn't exist\n", stuDir);
        return;
    } //현재 작업디렉터리 변경
    getcwd(stuDir, BUFLEN);
    //학생 디렉터리의 정보 저장
    chdir(saved_path); //정답 디렉터리 확인
    if(chdir(ansDir) < 0){
        fprintf(stderr, "%s doesn't exist\n", ansDir);
        return;
    } //정답디렉터리의 존재 유무 확인
    getcwd(ansDir, BUFLEN);
    //정답디렉터리 불러옴
    chdir(saved_path);
    //정답디렉터리 정보저장
    set_scoreTable(ansDir); //문제의 점수를 저장하는 csv파일을 생성
    set_idTable(stuDir); //학생의 득점을 저장하기 위한 csv 파일 생성

    if(mOption) {
        do_mOption();

    } //m옵션을 입력하였을 경우, m옵션 함수 실행

    printf("grading student's test papers..\n");
    score_students(); //학생들의 답안 채점

    if(iOption) 
        do_iOption(cIDs); //다른 조건들을 실행하고 i옵션이 있을 경우 실행함

    return;
}

void do_mOption(void) {
    int i, ft = 0;
    char tmp[30];
    int cnt;
    double ns;
    while(1) {
        printf("Input question's number to modify >> ");
        scanf("%s", tmp);
        ft = 0;
        if(!strcmp(tmp, "no"))
            break;
        //no라고 입력한 경우 문제 배점 수정 종료
        for(i = 0; i < QNUM; i++){
            cnt = strncmp(tmp, score_table[i].qname, strlen(tmp));
            if(!cnt) {
            printf("Current score : %.2lf\n", score_table[i].score);
            printf("New score : ");
            scanf("%lf", &ns);
            score_table[i].score = ns;
            ft = 1;
            }
        } //문제의 새 배점을 입력받아 출력함
        if(!ft) //사용자가 없는 문제 번호를 입력할 경우, 에러 출력 후 새 입력을 대기함
            printf("Wrong question number!!\n");
    } // break조건이 나올떄 까지 반복하여 입력받음
    write_scoreTable("score_table.csv"); //바뀐 배점으로 score_table을 새로 작성
    return;
} //m옵션이 주어졌을 경우 문제의 배점을 수정하는 함수



int check_option(int argc, char *argv[])
{ //입력된 옵션을 체크 하는 함수
    int i, j;
    int c;

    while((c = getopt(argc, argv, "me:ti:")) != -1)
    { //지정된 옵션이 입력되었는지 확인함
        switch(c){
            case 'm': //m옵션시 옵션 스위치를 켬
                mOption = true; 
                break;
            case 'e': //e옵션이 입렫외었을 경우 지정된 이름의 error 디렉터리를 생성함
                eOption = true;
                strcpy(errorDir, optarg);

                if(access(errorDir, F_OK) < 0)
                    mkdir(errorDir, 0755);
                else{
                    rmdirs(errorDir);
                    mkdir(errorDir, 0755);
                }
                break;
            case 't': //t옵션의 스위치를 켜고 어느 문제를 thread를 이용하여 채점할지 기억함
                tOption = true;
                i = optind;
                j = 0;

                while(i < argc && argv[i][0] != '-'){

                    if(j >= ARGNUM)
                        printf("Maximum Number of Argument Exceeded.  :: %s\n", argv[i]);
                    else
                        strcpy(threadFiles[j], argv[i]);
                    i++; 
                    j++;
                }
                break;
            case 'i': //i옵션 인 경우 어느 학생의 틀린 문제를 출력할지 저장함
                iOption = true;
                i = optind - 1;
                j = 0;
            
                while(i < argc && argv[i][0] != '-'){

                    if(j >= ARGNUM)
                        printf("Maximum Number of Argument Exceeded.  :: %s\n", argv[i]);
                    else
                        strcpy(cIDs[j], argv[i]);
                    i++; 
                    j++;
                }
                break;
            case '?': //그 외의 지정되지 않은 옵션이 들어올 경우 판단불가능을 반환함
                printf("Unknown option %c\n", optopt);
                return false;
        }
    } //모든 옵션을 판단한 후 while문 종료

    return true;
}


void do_iOption(char (*ids)[FILELEN])
{ //학생의 틀린 문제 번호를 출력하는 함수 -i 옵션을 위함
    FILE *fp;
    char tmp[BUFLEN];
    char ques_num[BUFLEN];
    char ques_num_backup[BUFLEN];
    int i = 0;
    char *p, *saved, *qn, *nextptr;
    
    if((fp = fopen("score.csv", "r")) == NULL){
        fprintf(stderr, "file open error for score.csv\n");
        return;
    } //score.csv를 오픈함, 실패시 에러출력
    
    fscanf(fp, "%s\n", ques_num);
    strcpy(ques_num_backup, ques_num);
    //문제번호 줄 읽어옴
    //printf("%s\n", ques_num);
    while(fscanf(fp, "%s\n", tmp) != EOF)
    {
        p = strtok(tmp, ",");
    
        if(!is_exist(ids, p))
            continue;
        //학생의 학번이 올바른지 판단함
        printf("%s's wrong answer :\n", p);
        strcpy(ques_num, ques_num_backup);
        qn = strtok_r(ques_num, ",", &nextptr);
        while((p = strtok(NULL, ",")) != NULL) {
        
            if(!strcmp(p, "0"))
                printf("%s ", qn);  
            qn = strtok_r(NULL, ",", &nextptr);
        } //학생의 점수가 0인 문제의 반호를 문제의 끝까지 출력함
        printf("\n");

    }
    fclose(fp);
}

int is_exist(char (*src)[FILELEN], char *target)
{ //입력된 학생의 학번이 실제로 목록에 존재하는지 확인하는 함수
    int i = 0;

    while(1)
    {
        if(i >= ARGNUM)
            return false;
        else if(!strcmp(src[i], ""))
            return false;
        else if(!strcmp(src[i++], target))
            return true;
    } //파일의 첫 줄부터 돌면서 학생이 존재하는지 확인함
    return false; //확인되지 않을 경우 false 반환
}

void set_scoreTable(char *ansDir)
{ //문제의 배점을 저장하는 함수
    char filename[FILELEN];

    sprintf(filename, "./%s", "score_table.csv"); //I changed
    //현재 디렉터리에 문제 배점 저장하는 파일 생성
    if(access(filename, F_OK) == 0)
        read_scoreTable(filename); //배점 파일을 읽어옴
    else{
        make_scoreTable(ansDir); //배점 파일을 만듦
        write_scoreTable(filename); //배점 파일을 저장함
    }
}

void read_scoreTable(char *path)
{ //배점 파일을 읽어오는 함수
    FILE *fp;
    char qname[FILELEN];
    char score[BUFLEN];
    int idx = 0;

    if((fp = fopen(path, "r")) == NULL){
        fprintf(stderr, "file open error for %s\n", path);
        return ;
    } // 배점 파일 열기

    while(fscanf(fp, "%[^,],%s\n", qname, score) != EOF){
        strcpy(score_table[idx].qname, qname);
        score_table[idx++].score = atof(score);
    } //문제 배점 파일을 한 줄 씩 읽어 문제 번호와 점수를 score_table 배열에 저장함

    fclose(fp);
}

void make_scoreTable(char *ansDir)
{ //score_table.csv 초기에 배점을 사용자에게 입력받는 함수
    int type, num;
    double score, bscore, pscore;
    struct dirent *dirp, *c_dirp;
    DIR *dp, *c_dp;
    char tmp[BUFLEN];
    int idx = 0;
    int i;

    num = get_create_type();
    //사용자의 메뉴 입력을 받아옴
    if(num == 1)
    {
        printf("Input value of blank question : ");
        scanf("%lf", &bscore);
        printf("Input value of program question : ");
        scanf("%lf", &pscore);
    } //빈칸 문제와 프로그램 눈제의 점수를 설정함

    if((dp = opendir(ansDir)) == NULL){
        fprintf(stderr, "open dir error for %s\n", ansDir);
        return;
    }   //dp는 정답 폴더의 디렉터리 포인터

    while((dirp = readdir(dp)) != NULL)
    {
        if(!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
            continue;

        sprintf(tmp, "./%s", dirp->d_name);
        if(get_file_type(dirp->d_name) != -1)
            strcpy(score_table[idx++].qname, dirp->d_name);
    }//정답 폴더에 있는 문제 번호를 불러옴, 어떠한 문제 번호들을 분석함

    closedir(dp);
    sort_scoreTable(idx); //문제번호 순으로 문제 정렬

    for(i = 0; i < idx; i++)
    {
        type = get_file_type(score_table[i].qname);
        //문제 번호를 보고 문제가 텍스트 문제인지 c프로그램 파일인지 구분함
        if(num == 1)
        { //사용자가 1번을 선택하였을 경우, 모든 빈칸문제는 bscore로, 모든 프로그램 문제는 pscore로 설정
            if(type == TEXTFILE)
                score = bscore;
            else if(type == CFILE)
                score = pscore;
        }
        else if(num == 2)
        { //사용자가 2번을 선택한 경우, 모든 문제에 대해 입력받음 
            printf("Input of %s: ", score_table[i].qname);
            scanf("%lf", &score);
        }
        //입력받은 점수를 score_table배열에 저장
        score_table[i].score = score;
    }
}

void write_scoreTable(char *filename)
{ //배열에 저장해 두었던 문제별 배점데이터를 csv 파일에 쓰는 함수
    int fd;
    char tmp[BUFLEN];
    int i;
    int num = sizeof(score_table) / sizeof(score_table[0]);

    if((fd = creat(filename, 0666)) < 0){
        fprintf(stderr, "creat error for %s\n", filename);
        return;
    } //score_table 파일을 생성함

    for(i = 0; i < num; i++)
    {
        if(score_table[i].score == 0)
            break;

        sprintf(tmp, "%s,%.2f\n", score_table[i].qname, score_table[i].score);
        write(fd, tmp, strlen(tmp));
    } //파일에 문제 번호와 점수를 저장함

    close(fd);
}


void set_idTable(char *stuDir)
{ //학생 디렉터리를 읽고 학번을 추출해서 저장하는 함수
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    char tmp[BUFLEN];
    int num = 0;

    if((dp = opendir(stuDir)) == NULL){
        fprintf(stderr, "opendir error for %s\n", stuDir);
        exit(1);
    } //학생들의 정답이 있는 폴더을 오픈함

    while((dirp = readdir(dp)) != NULL){
        if(!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
            continue;

        sprintf(tmp, "%s/%s", stuDir, dirp->d_name);
        stat(tmp, &statbuf);

        if(S_ISDIR(statbuf.st_mode))
            strcpy(id_table[num++], dirp->d_name);
        else
            continue;
    } //폴더안을 돌면서 학생의 학번을 수집하여 배열에 저장함

    sort_idTable(num); // 학번순으로 정렬
}

void sort_idTable(int size)
{ //불러와 저장한 학번을 정렬하는 함수
    int i, j;
    char tmp[10];

    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - 1 -i; j++){
            if(strcmp(id_table[j], id_table[j+1]) > 0){
                strcpy(tmp, id_table[j]);
                strcpy(id_table[j], id_table[j+1]);
                strcpy(id_table[j+1], tmp);
            }
        }
    }
}

void sort_scoreTable(int size)
{ //문제번호 순서대로 문제배점 배열을 정렬하는 함수
    int i, j;
    struct ssu_scoreTable tmp;
    int num1_1, num1_2;
    int num2_1, num2_2;

    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - 1 - i; j++){

            get_qname_number(score_table[j].qname, &num1_1, &num1_2);
            get_qname_number(score_table[j+1].qname, &num2_1, &num2_2);
            //비교를 위한 두개의 문제번호를 불러옴

            if((num1_1 > num2_1) || ((num1_1 == num2_1) && (num1_2 > num2_2))){

                memcpy(&tmp, &score_table[j], sizeof(score_table[0]));
                memcpy(&score_table[j], &score_table[j+1], sizeof(score_table[0]));
                memcpy(&score_table[j+1], &tmp, sizeof(score_table[0]));
            } // 문제번호순대로 배열의 원소를 교환함
        }
    }//버블 정렬을 이용하여 문제번호 순으로 정렬
}

void get_qname_number(char *qname, int *num1, int *num2)
{ //베열에서 문제번호를 불러오는 함수
    char *p;
    char dup[FILELEN];

    strncpy(dup, qname, strlen(qname));
    *num1 = atoi(strtok(dup, "-."));
    //문제 번호를 - 앞까지 끊어서 저장
    p = strtok(NULL, "-.");
    if(p == NULL)
        *num2 = 0;
    else
        *num2 = atoi(p);
} // - 이후로도 문제번호가 있을경우 별도로 .txt 또는 .c 앞까지 읽어서 저장

int get_create_type()
{ //초기에 문제배점 테이블이 없을때 사용자로부터 입력을 받기 위한 메뉴 함수
    int num;

    while(1)
    { //1번 모든 빈칸 문제 프로그램 문제를 한번에 설정함, 2번 각각의 문제에 대해 설정함
        printf("score_table.csv file doesn't exist!\n");
        printf("1. input blank question and program question's score. ex) 0.5 1\n");
        printf("2. input all question's score. ex) Input value of 1-1: 0.1\n");
        printf("select type >> ");
        scanf("%d", &num);

        if(num != 1 && num != 2)
            printf("not correct number!\n"); //1 또는 2가 들어올때 까지 반복
        else
            break;
    }

    return num; //사용자의 입력 반환
}

void score_students()
{ //학생들의 득점을 저장하는 함수
    double score = 0;
    int num;
    int fd;
    char tmp[BUFLEN];
    int size = sizeof(id_table) / sizeof(id_table[0]);

    if((fd = creat("score.csv", 0666)) < 0){
        fprintf(stderr, "creat error for score.csv");
        return;
    } //학생들의 점수를 저장할 파일을 생성함
    write_first_row(fd);   //score.csv에 문제번호 입력

    for(num = 0; num < size; num++)
    {
        if(!strcmp(id_table[num], ""))
            break;

        sprintf(tmp, "%s,", id_table[num]);
        write(fd, tmp, strlen(tmp)); 
        //처음에 학생의 학번 입력
        score += score_student(fd, id_table[num]);
    } //학생의 득점을 순차적으로 입력함 , score 변수에 평균 계산을 위해 학생의 총 득점을 더해둠

    printf("Total average : %.2f\n", score / num);
    //학생들의 총 평균 출력
    close(fd); //학생들의 득점 파일 close
}

double score_student(int fd, char *id)
{ //학생들의 점수를 실질적으로 계산하는 함수
    int type;
    double result;
    double score = 0;
    int i;
    char tmp[BUFLEN];
    int size = sizeof(score_table) / sizeof(score_table[0]);
    //문제 갯수만큼 for문을 돌리기 위해 문제 갯수 계산
    for(i = 0; i < size ; i++)
    {
        if(score_table[i].score == 0)
            break;

        sprintf(tmp, "%s/%s/%s", stuDir, id, score_table[i].qname);
        //학생들의 정답 위치로 이동
        if(access(tmp, F_OK) < 0)
            result = false;
        else
        {
            if((type = get_file_type(score_table[i].qname)) < 0)
                continue;
              //텍스트파일 또는 프로그램 파일이 아닐 경우 무시
            if(type == TEXTFILE)
                result = score_blank(id, score_table[i].qname);
            else if(type == CFILE)
                result = score_program(id, score_table[i].qname);
        } //빈칸문제일 경우 score_blank에서 점수 계산
        //프로그램 문제일 경우 score_program에서 점수 계산

        if(result == false)
            write(fd, "0,", 2); //틀렸을 경우 0점 입력
        else{
            if(result == true){
                score += score_table[i].score;
                sprintf(tmp, "%.2f,", score_table[i].score);
            }//맞았을 경우 배열에 점수 저장, 학생의 총점 계산을 위해 score에 저장
            else if(result < 0){
                score = score + score_table[i].score + result;
                sprintf(tmp, "%.2f,", score_table[i].score + result);
            } //result가 0보다 작을 경우 감점도 점수에 더해줌
            write(fd, tmp, strlen(tmp));
        } //계산된 점수를 씀
    }


    printf("%s is finished.. score : %.2f\n", id, score); 
    //점수 계산이 끝난 후 학생별 점수 출력

    sprintf(tmp, "%.2f\n", score);
    write(fd, tmp, strlen(tmp));
    //학생의 총점을 파일에 쓰고 반환함
    return score;
}

void write_first_row(int fd)
{ // 학생 배점 파일 첫줄에 문제 번호를 작성하는 함수
    int i;
    char tmp[BUFLEN];
    int size = sizeof(score_table) / sizeof(score_table[0]);

    write(fd, ",", 1);
    //가장 왼쪽 위의 칸은 빈칸
    for(i = 0; i < size; i++){
        if(score_table[i].score == 0)
            break;
          //문제의 끝에 도달하면 읽기 종료
        sprintf(tmp, "%s,", score_table[i].qname);
        write(fd, tmp, strlen(tmp));
    }
    write(fd, "sum\n", 4); // 문제 번호를 입력하고 마지막에 sum 입력칸을 만들어줌
} 

char *get_answer(int fd, char *result)
{ //답안에서 정답을 뽑아오는 함수
    char c;
    int idx = 0;

    memset(result, 0, BUFLEN);
    while(read(fd, &c, 1) > 0)
    {
        if(c == ':')
            break;
          //정답을 콜론으로 구분하여 하나씩 추출함
        result[idx++] = c;
    }
    if(result[strlen(result) - 1] == '\n')
        result[strlen(result) - 1] = '\0';
      //개행 문자를 널문자로 교체하여 문장의 끝 표시
    return result;
}

int score_blank(char *id, char *filename)
{ //빈칸 문제 채점 함수
    char tokens[TOKEN_CNT][MINLEN];
    node *std_root = NULL, *ans_root = NULL;
    int idx, start;
    char tmp[BUFLEN];
    char s_answer[BUFLEN], a_answer[BUFLEN];
    char qname[FILELEN];
    int fd_std, fd_ans;
    int result = true;
    int has_semicolon = false;

    memset(qname, 0, sizeof(qname));
    memcpy(qname, filename, strlen(filename) - strlen(strrchr(filename, '.')));

    sprintf(tmp, "%s/%s/%s", stuDir, id, filename);
    fd_std = open(tmp, O_RDONLY);
    strcpy(s_answer, get_answer(fd_std, s_answer));
    //학생답을 불러옴

    if(!strcmp(s_answer, "")){
        close(fd_std);
        return false;
    } //학생 답이 없으면 0점 처리

    if(!check_brackets(s_answer)){
        close(fd_std);
        return false;
    } //괄호 갯수가 맞지 않으면 0점 처리

    strcpy(s_answer, ltrim(rtrim(s_answer)));
    //왼쪽 오른쪽 공백 지우기
    if(s_answer[strlen(s_answer) - 1] == ';'){
        has_semicolon = true; //세미콜론 유무 확인
        s_answer[strlen(s_answer) - 1] = '\0'; //세미콜론 삭제
    }

    if(!make_tokens(s_answer, tokens)){
        close(fd_std);
        return false;
    } //토큰 만들기

    idx = 0;
    std_root = make_tree(std_root, tokens, &idx, 0);
    //학생 정답을 이용해서 트리를 생성함
    sprintf(tmp, "%s/%s", ansDir, filename); //정답 파일 열기
    fd_ans = open(tmp, O_RDONLY); //정답파일 불러오기

    while(1)
    {
        ans_root = NULL; //정답이 여러개일수 있으니 NULL
        result = true;

        for(idx = 0; idx < TOKEN_CNT; idx++)
            memset(tokens[idx], 0, sizeof(tokens[idx]));
        //토큰 초기화
        strcpy(a_answer, get_answer(fd_ans, a_answer));

        if(!strcmp(a_answer, ""))
            break;
        //정답 파일이 비었을 경우 break
        strcpy(a_answer, ltrim(rtrim(a_answer)));
        //정답의 양쪽 공백 제거
        if(has_semicolon == false){
            if(a_answer[strlen(a_answer) -1] == ';')
                continue;
        }

        else if(has_semicolon == true)
        {
            if(a_answer[strlen(a_answer) - 1] != ';')
                continue;
            else
                a_answer[strlen(a_answer) - 1] = '\0';
        }

        if(!make_tokens(a_answer, tokens))
            continue; //정답 파일에 대한 토큰 생성

        idx = 0;
        ans_root = make_tree(ans_root, tokens, &idx, 0);
        //정답파일의 토큰을 이용해서 트리 생성
        compare_tree(std_root, ans_root, &result);
        // 학생의 정답 트리와 정답지의 트리를 서로 비교한다
        if(result == true){
            close(fd_std);
            close(fd_ans);

            if(std_root != NULL)
                free_node(std_root);
            if(ans_root != NULL)
                free_node(ans_root);
            return true;
            //트리가 일치 할 경우 정답처리
        }
    }

    close(fd_std);
    close(fd_ans);

    if(std_root != NULL)
        free_node(std_root);
    if(ans_root != NULL)
        free_node(ans_root);

    return false;
} //트리가 같지 않을 경우 오답 처리

double score_program(char *id, char *filename)
{ //프로그램 문제를 채점하는 함수
    double compile;
    int result;

    compile = compile_program(id, filename);
    //컴파일 한 결과를 받아와서 판단함
    if(compile == ERROR || compile == false)
        return false;
    //컴파일이 안되거나 에러가 나올 경우 오답처리
    result = execute_program(id, filename);
    //컴파일이 된 프로그램 문제에 대해 실행 여부 확인
    if(!result)
        return false;
    //결과가 다를 경우 오답 처리
    if(compile < 0)
        return compile;
    //오류 발생시 감점 적용
    return true; //맞았을 경우 정답 처리
}

int is_thread(char *qname)
{ //t옵션을 적용해야 하는 문제인지 배열에서 검색하는 함수
    int i;
    int size = sizeof(threadFiles) / sizeof(threadFiles[0]);

    for(i = 0; i < size; i++){
        if(!strcmp(threadFiles[i], qname))
            return true;
    }
    return false;
} //t 옵션으로 지정된 문제 번호에 컴파일시  -lpthread 옵션 추가

double compile_program(char *id, char *filename)
{ //프로그램 문제를 컴파일 하는 함수
    int fd;
    char tmp_f[BUFLEN], tmp_e[BUFLEN];
    char command[BUFLEN];
    char qname[FILELEN];
    int isthread;
    off_t size;
    double result;

    memset(qname, 0, sizeof(qname));
    memcpy(qname, filename, strlen(filename) - strlen(strrchr(filename, '.')));

    isthread = is_thread(qname);
    //-t 옵션으로 지정된 문제인지 판단
    sprintf(tmp_f, "%s/%s", ansDir, filename);
    sprintf(tmp_e, "%s/%s.exe", ansDir, qname);

    if(tOption && isthread)
        sprintf(command, "gcc -o %s %s -lpthread", tmp_e, tmp_f);
    else
        sprintf(command, "gcc -o %s %s", tmp_e, tmp_f);
      //t옵션이 적용된 문제의 경우 -lpthread 옵션 추가
    sprintf(tmp_e, "%s/%s/%s_error.txt", ansDir, qname, qname);
    fd = creat(tmp_e, 0666);
    //e옵션이 적용되어있는 경우, 오류메시지를 지정한 디렉터리에 텍스트 파일로 저장함
    redirection(command, fd, STDERR);
    size = lseek(fd, 0, SEEK_END);
    close(fd);
    unlink(tmp_e);

    if(size > 0)
        return false;

    sprintf(tmp_f, "%s/%s/%s", stuDir, id, filename);
    sprintf(tmp_e, "%s/%s/%s.stdexe", stuDir, id, qname);

    if(tOption && isthread)
        sprintf(command, "gcc -o %s %s -lpthread", tmp_e, tmp_f);
    else
        sprintf(command, "gcc -o %s %s", tmp_e, tmp_f);
    // t옵션의 유무에 따라 컴파일을 다르게 적용함
    sprintf(tmp_f, "%s/%s/%s_error.txt", stuDir, id, qname);
    fd = creat(tmp_f, 0666);
    //에러 파일은 다른 곳로 출력함
    redirection(command, fd, STDERR); // STDERR의 fd를 다른 파일로 옮김
    size = lseek(fd, 0, SEEK_END); //파일 끝으로 가서 파일의 사이즈를 판단함
    close(fd);

    if(size > 0){
        if(eOption)
        { //e옵션이 있을 경우 오류메시지를 사용자가 지정한 폴더로 내보냄
            sprintf(tmp_e, "%s/%s", errorDir, id);
            if(access(tmp_e, F_OK) < 0)
                mkdir(tmp_e, 0755);

            sprintf(tmp_e, "%s/%s/%s_error.txt", errorDir, id, qname);
            rename(tmp_f, tmp_e);

            result = check_error_warning(tmp_e);
        }
        else{ //e옵션이 없을 경우 에러나 경고의 갯수만을 판단함 
            result = check_error_warning(tmp_f);
            unlink(tmp_f);
        }

        return result;
    }

    unlink(tmp_f);
    return true;
}

double check_error_warning(char *filename)
{ //학생들의 프로그램에서 에러 또는 경고의 갯수를 계산하는 함수
    FILE *fp;
    char tmp[BUFLEN];
    double warning = 0;

    if((fp = fopen(filename, "r")) == NULL){
        fprintf(stderr, "fopen error for %s\n", filename);
        return false;
    }

    while(fscanf(fp, "%s", tmp) > 0){
        if(!strcmp(tmp, "error:"))
            return ERROR;
        else if(!strcmp(tmp, "warning:"))
            warning += WARNING;
    }
    //warning의 갯수만큼 -0.1점함, error 발생시 0점
    return warning;
}

int execute_program(char *id, char *filename)
{ //학생들의 프로그램 문제를 실행하는 함수
    char std_fname[BUFLEN], ans_fname[BUFLEN];
    char tmp[BUFLEN];
    char qname[FILELEN];
    time_t start, end;
    pid_t pid;
    int fd;

    memset(qname, 0, sizeof(qname));
    memcpy(qname, filename, strlen(filename) - strlen(strrchr(filename, '.')));

    sprintf(ans_fname, "%s/%s.stdout", ansDir, qname);
    fd = creat(ans_fname, 0666);

    sprintf(tmp, "%s/%s.exe", ansDir, qname);
    redirection(tmp, fd, STDOUT); //프로그램 문제 정답 프로그램의 표준 출력을 임시 파일로 돌림
    close(fd);

    sprintf(std_fname, "%s/%s/%s.stdout", stuDir, id, qname);
    fd = creat(std_fname, 0666);

    sprintf(tmp, "%s/%s/%s.stdexe &", stuDir, id, qname);

    start = time(NULL);
    redirection(tmp, fd, STDOUT); //학생들의 프로그램 문제의 표준 출력을 임시 파일로 돌림

    sprintf(tmp, "%s.stdexe", qname);
    while((pid = inBackground(tmp)) > 0){ //백그라운드에서 돌고 있는 학생 프로그램의 프로세스 ID를 가져옴
        end = time(NULL);

        if(difftime(end, start) > OVER){ //5초이상 소요되었을 경우 프로세스를 KILL하고 0점 부여
            kill(pid, SIGKILL);
            close(fd);
            return false;
        }
    }

    close(fd);
    //마지막으로 결과 파일을 비교하여 점수를 부여함
    return compare_resultfile(std_fname, ans_fname);
}

pid_t inBackground(char *name)
{//백그라운드에서 실행중인 학생 또는 정답 프로그램의 프로세스 ID를 반환함
    pid_t pid;
    char command[64];
    char tmp[64];
    int fd;
    off_t size;

    memset(tmp, 0, sizeof(tmp));
    fd = open("background.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    //백그라운드에서 돌아가는 프로그램의 pid를 파일 하나에 저장해둠
    sprintf(command, "ps | grep %s", name);
    redirection(command, fd, STDOUT); //프로그램의 표준 출력을 다른 파일로 변경함

    lseek(fd, 0, SEEK_SET);
    read(fd, tmp, sizeof(tmp));

    if(!strcmp(tmp, "")){
        unlink("background.txt");
        close(fd);
        return 0;
    }

    pid = atoi(strtok(tmp, " "));
    close(fd);

    unlink("background.txt"); //파일 삭제
    return pid;
}

int compare_resultfile(char *file1, char *file2)
{ //결과물 파일 두개를 서로 비교함
    int fd1, fd2;
    char c1, c2;
    int len1, len2;

    fd1 = open(file1, O_RDONLY);
    fd2 = open(file2, O_RDONLY);

    while(1)
    {
        while((len1 = read(fd1, &c1, 1)) > 0){
            if(c1 == ' ') 
                continue;
            else 
                break;
        }
        while((len2 = read(fd2, &c2, 1)) > 0){
            if(c2 == ' ') 
                continue;
            else 
                break;
        } //각 파일에서 한글자씩 읽어옴

        if(len1 == 0 && len2 == 0)
            break;
        //파일이 끝났을 경우 종료
        to_lower_case(&c1);
        to_lower_case(&c2);
        //각 글자를 소문자로 변환한다
        if(c1 != c2){
            close(fd1);
            close(fd2);
            return false;
        } //글자가 서로 다를 경우 false를 리턴
    }
    close(fd1);
    close(fd2);
    return true;
} //글자가 다른 경우가 없을 경우 파일을 닫고 true를 리턴

void redirection(char *command, int new, int old)
{ //파일 디스크립터를 덮어썼다가 다시 복구 시켜주는 함수
    int saved, saved2;

    saved = dup(old);
    saved2 = dup(STDERR);
    dup2(new, old);
    dup2(new, STDERR);

    system(command);

    dup2(saved, old);
    
    close(saved);
    close(saved2);
} // 학생 및 정답 프로그램 파일에서 오류나 출력값이 나올때 화면이 아닌 임의의 파일로 출력하는데 사용

int get_file_type(char *filename)
{
    char *extension = strrchr(filename, '.');

    if(!strcmp(extension, ".txt"))
        return TEXTFILE;
    else if (!strcmp(extension, ".c"))
        return CFILE;
    else
        return -1;
} //파일의 확장자를 통해 텍스트파일과 C파일을 구분함

void rmdirs(const char *path)
{ //입력된 디렉터리를 삭제하는데에 사용하는 함수
    struct dirent *dirp;
    struct stat statbuf;
    DIR *dp;
    char tmp[1024];

    if((dp = opendir(path)) == NULL)
        return;

    while((dirp = readdir(dp)) != NULL)
    {
        if(!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
            continue;

        sprintf(tmp, "%s/%s", path, dirp->d_name);

        if(lstat(tmp, &statbuf) == -1)
            continue;

        if(S_ISDIR(statbuf.st_mode))
            rmdirs(tmp);
        else
            unlink(tmp);
    } //디렉터리를 읽어서 내부에 디렉터리가 존재할 경우 디렉터리를 삭제함

    closedir(dp);
    rmdir(path);
}

void to_lower_case(char *c)
{ //모두 소문자로 전환함
    if(*c >= 'A' && *c <= 'Z')
        *c = *c + 32;
}

void print_usage() //-h 옵션일때 사용 방법 출력
{
    printf("Usage : ssu_score <STUDENTDIR> <TRUEDIR> [OPTION]\n");
    printf("Option : \n");
    printf(" -e <DIRNAME>      print error on 'DIRNAME/ID/qname_error.txt' file \n");
    printf(" -t <QNAMES>       compile QNAME.C with -lpthread option\n");
    printf(" -h                print usage\n");
    printf(" -p                print student's score and total average\n");
    printf(" -i <IDS>          print ID's wrong questions\n");
}

