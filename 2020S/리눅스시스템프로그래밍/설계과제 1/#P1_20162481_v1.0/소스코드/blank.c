#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "blank.h"

char datatype[DATATYPE_SIZE][MINLEN] = {"int", "char", "double", "float", "long"
    , "short", "ushort", "FILE", "DIR","pid"
        ,"key_t", "ssize_t", "mode_t", "ino_t", "dev_t"
        , "nlink_t", "uid_t", "gid_t", "time_t", "blksize_t"
        , "blkcnt_t", "pid_t", "pthread_mutex_t", "pthread_cond_t", "pthread_t"
        , "void", "size_t", "unsigned", "sigset_t", "sigjmp_buf"
        , "rlim_t", "jmp_buf", "sig_atomic_t", "clock_t", "struct"};

 //연산자 우선순위 저장
operator_precedence operators[OPERATOR_CNT] = {
    {"(", 0}, {")", 0}
    ,{"->", 1}  
    ,{"*", 4}   ,{"/", 3}   ,{"%", 2}   
    ,{"+", 6}   ,{"-", 5}   
    ,{"<", 7}   ,{"<=", 7}  ,{">", 7}   ,{">=", 7}
    ,{"==", 8}  ,{"!=", 8}
    ,{"&", 9}
    ,{"^", 10}
    ,{"|", 11}
    ,{"&&", 12}
    ,{"||", 13}
    ,{"=", 14}  ,{"+=", 14} ,{"-=", 14} ,{"&=", 14} ,{"|=", 14}
};

void compare_tree(node *root1,  node *root2, int *result)
{ // 정답과 학생의 답으로 만든 트리를 서로 비교하는 함수
    node *tmp;
    int cnt1, cnt2;

    if(root1 == NULL || root2 == NULL){
        *result = false;
        return;
    } //트리가 없으면 끝

    if(!strcmp(root1->name, "<") || !strcmp(root1->name, ">") || !strcmp(root1->name, "<=") || !strcmp(root1->name, ">=")){
        if(strcmp(root1->name, root2->name) != 0){

            if(!strncmp(root2->name, "<", 1))
                strncpy(root2->name, ">", 1);

            else if(!strncmp(root2->name, ">", 1))
                strncpy(root2->name, "<", 1);

            else if(!strncmp(root2->name, "<=", 2))
                strncpy(root2->name, ">=", 2);

            else if(!strncmp(root2->name, ">=", 2))
                strncpy(root2->name, "<=", 2);

            root2 = change_sibling(root2);
        }
    } //첫 노드가 부등호일 경우 두 트리의 부등호 뱡향을 통일 시키기 위해 자식 노드를 교환함

    if(strcmp(root1->name, root2->name) != 0){
        *result = false;
        return;
    } //트리 시작이 다르면 false 리턴

    if((root1->child_head != NULL && root2->child_head == NULL)
            || (root1->child_head == NULL && root2->child_head != NULL)){
        *result = false;
        return;
    } //자식 노드의 시작이 달라도 false 리턴

    else if(root1->child_head != NULL){
        if(get_sibling_cnt(root1->child_head) != get_sibling_cnt(root2->child_head)){
            *result = false;
            return;
        } //자식 노드의 갯수가 다르면 false 리턴

        if(!strcmp(root1->name, "==") || !strcmp(root1->name, "!="))
        {// 트리의 시작이 비교 연산자일 경우
            compare_tree(root1->child_head, root2->child_head, result);
            //루트 노드의 자식 노드를 비교함
            if(*result == false)
            {
                *result = true;
                root2 = change_sibling(root2);
                compare_tree(root1->child_head, root2->child_head, result);
            } //false가 나왔을 경우 자식 노드의 순서를 바꿔서 다시 확인함
        }
        else if(!strcmp(root1->name, "+") || !strcmp(root1->name, "*")
                || !strcmp(root1->name, "|") || !strcmp(root1->name, "&")
                || !strcmp(root1->name, "||") || !strcmp(root1->name, "&&"))
        {//트리의 시작이 + * | || & && 일 경우
            if(get_sibling_cnt(root1->child_head) != get_sibling_cnt(root2->child_head)){
                *result = false;
                return;
            } //자식 노드 갯수가 다르면 false

            tmp = root2->child_head;

            while(tmp->prev != NULL)
                tmp = tmp->prev;
            //마지막 자식노드로 이동
            while(tmp != NULL)
            { // 학생 트리와 정답 트리의 같은 깊이의 자식들을 서로 비교함
                compare_tree(root1->child_head, tmp, result);

                if(*result == true)
                    break;
                else{
                    if(tmp->next != NULL)
                        *result = true;
                    tmp = tmp->next;
                }
            }
        }
        else{ //루트 다음 단계의 노드들끼리의 비교를 시작함
            compare_tree(root1->child_head, root2->child_head, result);
        }
    }   


    if(root1->next != NULL){
        //최상위 노드의 형제 노드가 있을 경우
        if(get_sibling_cnt(root1) != get_sibling_cnt(root2)){
            *result = false;
            return;
        } //형제 노드의 갯수를 비교하고 갯수가 다를 경우 false 리턴

        if(*result == true)
        {
            tmp = get_operator(root1);
            //최상위 노드의 연산자를 가져옴
            if(!strcmp(tmp->name, "+") || !strcmp(tmp->name, "*")
                    || !strcmp(tmp->name, "|") || !strcmp(tmp->name, "&")
                    || !strcmp(tmp->name, "||") || !strcmp(tmp->name, "&&"))
            { //최상위 노드의 연산자가 위의 종류중에 있을경우 
                tmp = root2;

                while(tmp->prev != NULL)
                    tmp = tmp->prev;
                //형제 노드의 마지막으로 이동
                while(tmp != NULL)
                {
                    compare_tree(root1->next, tmp, result);

                    if(*result == true)
                        break;
                    else{
                        if(tmp->next != NULL)
                            *result = true;
                        tmp = tmp->next;
                    }
                } // 그 노드의 형제 노드들을 비교함
            }

            else //또는 그 다음 단계의 노드를 비교하기 시작함
                compare_tree(root1->next, root2->next, result);
        }
    }
}

int make_tokens(char *str, char tokens[TOKEN_CNT][MINLEN])
{ //학생의 답과 빈칸의 정답을 토큰으로 분해하는 함수
    char *start, *end;
    char tmp[BUFLEN];
    char str2[BUFLEN];
    char *op = "(),;><=!|&^/+-*\""; 
    int row = 0;
    int i;
    int isPointer;
    int lcount, rcount;
    int p_str;

    clear_tokens(tokens);
    //시작전 토큰 NULL로 초기화
    start = str;

    if(is_typeStatement(str) == 0) 
        return false;   
    //명령어는 빼버림
    while(1)
    {
        if((end = strpbrk(start, op)) == NULL)
            break;
        //더이상 연산자가 없는 경우 종료
        if(start == end){

            if(!strncmp(start, "--", 2) || !strncmp(start, "++", 2)){
                if(!strncmp(start, "++++", 4)||!strncmp(start,"----",4))
                    return false;
                //문자열의 시작이 ++, --, ++++, ----일 경우 false 반환
                if(is_character(*ltrim(start + 2))){ //왼쪽 공백을 지운것이 문자일 경우
                    if(row > 0 && is_character(tokens[row - 1][strlen(tokens[row - 1]) - 1]))
                        return false; 
                    //
                    end = strpbrk(start + 2, op); //연산자가 나오는 앞까지 end로 저장
                    if(end == NULL) //문자열에 연산자가 없는경우
                        end = &str[strlen(str)];
                    while(start < end) {
                        if(*(start - 1) == ' ' && is_character(tokens[row][strlen(tokens[row]) - 1]))
                            return false;
                        else if(*start != ' ')
                            strncat(tokens[row], start, 1);
                        start++;    
                    }
                }

                else if(row>0 && is_character(tokens[row - 1][strlen(tokens[row - 1]) - 1])){
                    if(strstr(tokens[row - 1], "++") != NULL || strstr(tokens[row - 1], "--") != NULL)  
                        return false;
                    //row열에 있는 토큰이 문자일 경우
                    memset(tmp, 0, sizeof(tmp));
                    strncpy(tmp, start, 2);
                    strcat(tokens[row - 1], tmp);// 토큰으로 만들어서 저장
                    start += 2;
                    row--;
                }
                else{
                    memset(tmp, 0, sizeof(tmp));
                    strncpy(tmp, start, 2);
                    strcat(tokens[row], tmp);
                    start += 2;
                }
            }

            else if(!strncmp(start, "==", 2) || !strncmp(start, "!=", 2) || !strncmp(start, "<=", 2)
                    || !strncmp(start, ">=", 2) || !strncmp(start, "||", 2) || !strncmp(start, "&&", 2) 
                    || !strncmp(start, "&=", 2) || !strncmp(start, "^=", 2) || !strncmp(start, "!=", 2) 
                    || !strncmp(start, "|=", 2) || !strncmp(start, "+=", 2) || !strncmp(start, "-=", 2) 
                    || !strncmp(start, "*=", 2) || !strncmp(start, "/=", 2)){
                //문자열이 위의 연산자와 같은경우
                strncpy(tokens[row], start, 2);
                start += 2;
            }//토큰으로 저장하고 2칸 전진
            else if(!strncmp(start, "->", 2))
            {//멤버 포인터 연산자일 경우
                end = strpbrk(start + 2, op);
                //연산자가 나올때까지 끊어서 end에 저장함
                if(end == NULL)
                    end = &str[strlen(str)];

                while(start < end){
                    if(*start != ' ')
                        strncat(tokens[row - 1], start, 1);
                    start++;
                }
                row--;
            }
            else if(*end == '&')
            { //'&'연산자 일때

                if(row == 0 || (strpbrk(tokens[row - 1], op) != NULL)){
                    end = strpbrk(start + 1, op);
                    if(end == NULL)
                        end = &str[strlen(str)];

                    strncat(tokens[row], start, 1);
                    start++;
                    //start를 토큰으로 저장
                    while(start < end){
                        if(*(start - 1) == ' ' && tokens[row][strlen(tokens[row]) - 1] != '&')
                            return false;
                        else if(*start != ' ')
                            strncat(tokens[row], start, 1);
                        start++;
                    }//직전에 만든 토큰이 &가 아닐때 새로 토큰을 만들어 저장
                }

                else{
                    strncpy(tokens[row], start, 1);
                    start += 1;
                }

            }
            else if(*end == '*')
            { //end가 *를 가리킬 떄
                isPointer=0;

                if(row > 0)
                {

                    for(i = 0; i < DATATYPE_SIZE; i++) { //DS는 35
                        if(strstr(tokens[row - 1], datatype[i]) != NULL){
                            strcat(tokens[row - 1], "*");
                            start += 1; 
                            isPointer = 1;
                            break;
                        }//datatype과 같지 않으면 새 토큰으로 * 추가
                    }
                    if(isPointer == 1)
                        continue;
                    if(*(start+1) !=0)
                        end = start + 1;


                    if(row>1 && !strcmp(tokens[row - 2], "*") && (all_star(tokens[row - 1]) == 1)){
                        strncat(tokens[row - 1], start, end - start);
                        row--;
                    }//토큰에 start의 길이만큼 복사해 넣음


                    else if(is_character(tokens[row - 1][strlen(tokens[row - 1]) - 1]) == 1){ 
                        strncat(tokens[row], start, end - start);   
                    }//전 토큰의 마지막이 문자일때, 새 토큰으로 하나 생성


                    else if(strpbrk(tokens[row - 1], op) != NULL){      
                        strncat(tokens[row] , start, end - start); 
                    }// 전 토큰에 연산자 전까지 NULL이 아니라면 새 토큰 생성
                    else
                        strncat(tokens[row], start, end - start);
                    //새 토큰 생성
                    start += (end - start);
                } //문자열 길이만큼 진행

                else if(row == 0)
                { //토큰이 하나도 없을 때
                    if((end = strpbrk(start + 1, op)) == NULL){
                        strncat(tokens[row], start, 1);
                        start += 1;
                    } // 문자열에 연산자 전으로 아무것도 없을 때, 한바이트 만큼 토큰 생성
                    else{
                        while(start < end){
                            if(*(start - 1) == ' ' && is_character(tokens[row][strlen(tokens[row]) - 1]))
                                return false;
                            else if(*start != ' ')
                                strncat(tokens[row], start, 1);
                            start++;    
                        }//공백이 아닐 경우 문자 하나만큼 토큰으로 만듬
                        if(all_star(tokens[row]))
                            row--;
                        //토큰이 *문자일 경우 row 하나 감소
                    }
                }
            }
            else if(*end == '(') 
            { //토큰의 시작이 '('일경우
                lcount = 0;
                rcount = 0;
                if(row>0 && (strcmp(tokens[row - 1],"&") == 0 || strcmp(tokens[row - 1], "*") == 0)){
                    while(*(end + lcount + 1) == '(')
                        lcount++;
                    start += lcount;

                    end = strpbrk(start + 1, ")");
                    //닫는 괄호 나올때까지 end에 저장
                    if(end == NULL)
                        return false; //닫는 괄호 없으면 문제 있는거
                    else{
                        while(*(end + rcount +1) == ')')
                            rcount++;
                        end += rcount;

                        if(lcount != rcount)
                            return false;
                        //여는 괄호와 닫는 괄호의 갯수가 달라도 문제 있는 것
                        if( (row > 1 && !is_character(tokens[row - 2][strlen(tokens[row - 2]) - 1])) || row == 1){ 
                            strncat(tokens[row - 1], start + 1, end - start - rcount - 1);
                            row--;
                            start = end + 1;
                        }//1번 줄이거나 row가 1보다 클때, 전 토큰의 마지막이 문자일떄
                        else{
                            strncat(tokens[row], start, 1);
                            start += 1;
                        }//새 토큰 생성
                    }

                }
                else{
                    strncat(tokens[row], start, 1);
                    start += 1;
                }

            }
            else if(*end == '\"') 
            {//문자열이 큰 따옴표일 때
                end = strpbrk(start + 1, "\"");
                //다시 큰따옴표가 나올때까지 end에 저장
                if(end == NULL)
                    return false;
                //큰따옴표가 없으면 문제 있는 것
                else{
                    strncat(tokens[row], start, end - start + 1);
                    start = end + 1;
                } //따옴표를 제외한 부분을 새 토큰으로 생성

            }

            else{ //그 외의 문자열일때
                if(row > 0 && !strcmp(tokens[row - 1], "++"))
                    return false;

                //전의 토큰이 ++ 이였으면 false
                if(row > 0 && !strcmp(tokens[row - 1], "--"))
                    return false;
                //전의 토큰이 --였으면 false
                strncat(tokens[row], start, 1);
                start += 1;
                //start에서 토큰으로 한 문자를 불러옴

                if(!strcmp(tokens[row], "-") || !strcmp(tokens[row], "+") || !strcmp(tokens[row], "--") || !strcmp(tokens[row], "++")){
                    //현재 토큰이 -, +, --, ++일경우
                    if(row == 0)
                        row--;

                    else if(!is_character(tokens[row - 1][strlen(tokens[row - 1]) - 1])){

                        if(strstr(tokens[row - 1], "++") == NULL && strstr(tokens[row - 1], "--") == NULL)
                            row--;
                    }//토큰이 ++ 또는 --가 아닌 경우 전의 토큰으로 올라감
                }
            }
        }
        else{  //start == end가 아닐떄
            if(all_star(tokens[row - 1]) && row > 1 && !is_character(tokens[row - 2][strlen(tokens[row - 2]) - 1]))   
                row--;              

            if(all_star(tokens[row - 1]) && row == 1)   
                row--;  
            //row가 1이고 첫번째 토큰이 * 문자일때
            for(i = 0; i < end - start; i++){
                if(i > 0 && *(start + i) == '.'){
                    strncat(tokens[row], start + i, 1);

                    while( *(start + i +1) == ' ' && i< end - start )
                        i++; 
                }
                else if(start[i] == ' '){
                    while(start[i] == ' ')
                        i++;
                    break;
                } //start에서 공백을 제외한 부분을 토큰으로 저장함
                else
                    strncat(tokens[row], start + i, 1);
            }

            if(start[0] == ' '){
                start += i;
                continue;
            }
            start += i;
        }

        strcpy(tokens[row], ltrim(rtrim(tokens[row])));
        //토큰의 좌우에서 공백까지 제거함
        if(row > 0 && is_character(tokens[row][strlen(tokens[row]) - 1]) 
                && (is_typeStatement(tokens[row - 1]) == 2 
                    || is_character(tokens[row - 1][strlen(tokens[row - 1]) - 1])
                    || tokens[row - 1][strlen(tokens[row - 1]) - 1] == '.' ) ){

            if(row > 1 && strcmp(tokens[row - 2],"(") == 0)
            {//여는 괄호가 있을떄
                if(strcmp(tokens[row - 1], "struct") != 0 && strcmp(tokens[row - 1],"unsigned") != 0)
                    return false;
            }//괄호 안에 struct나 unsigned가 있으면 false리턴
            else if(row == 1 && is_character(tokens[row][strlen(tokens[row]) - 1])) {
                if(strcmp(tokens[0], "extern") != 0 && strcmp(tokens[0], "unsigned") != 0 && is_typeStatement(tokens[0]) != 2)  
                    return false;
            }//토큰의 마지막이 문자일때 가장 처음의 토큰이 extern 또는 unsigned 일 경우 false 리턴
            else if(row > 1 && is_typeStatement(tokens[row - 1]) == 2){
                if(strcmp(tokens[row - 2], "unsigned") != 0 && strcmp(tokens[row - 2], "extern") != 0)
                    return false;
            }// 전 토큰이 명령어 일 때, 그 전의 토큰이 unsigned 또는 extern일때, false 리턴

        }

        if((row == 0 && !strcmp(tokens[row], "gcc")) ){
            clear_tokens(tokens);
            strcpy(tokens[0], str); 
            return 1;
        } //토큰이 gcc 일 경우 토큰을 초기화하고 str을 첫번째 토큰으로 복사함
        row++;
    }

    if(all_star(tokens[row - 1]) && row > 1 && !is_character(tokens[row - 2][strlen(tokens[row - 2]) - 1]))  
        row--;              
    if(all_star(tokens[row - 1]) && row == 1)   
        row--;  
    //start의 길이 만큼 start를 분석함
    for(i = 0; i < strlen(start); i++)   
    {
        if(start[i] == ' ')  
        {
            while(start[i] == ' ')
                i++;
            if(start[0]==' ') {
                start += i;
                i = 0;
            }//처음 공백 제거
            else
                row++;

            i--;
        } 
        else
        {
            strncat(tokens[row], start + i, 1);
            if( start[i] == '.' && i<strlen(start)){
                while(start[i + 1] == ' ' && i < strlen(start))
                    i++;
                //공백이 아닐때까지 start 포인터를 이동시켜서 한 문자를 토큰으로 가져옴
            }
        }
        strcpy(tokens[row], ltrim(rtrim(tokens[row])));
        //토큰의 좌우에서 공백까지 제거함
        if(!strcmp(tokens[row], "lpthread") && row > 0 && !strcmp(tokens[row - 1], "-")){ 
            strcat(tokens[row - 1], tokens[row]);
            memset(tokens[row], 0, sizeof(tokens[row]));
            row--;
        }
        else if(row > 0 && is_character(tokens[row][strlen(tokens[row]) - 1]) 
                && (is_typeStatement(tokens[row - 1]) == 2 
                    || is_character(tokens[row - 1][strlen(tokens[row - 1]) - 1])
                    || tokens[row - 1][strlen(tokens[row - 1]) - 1] == '.') ){

            if(row > 1 && strcmp(tokens[row-2],"(") == 0)
            {//여는 괄호가 있을떄
                if(strcmp(tokens[row-1], "struct") != 0 && strcmp(tokens[row-1], "unsigned") != 0)
                    return false;
            }//괄호 안에 struct나 unsigned가 있으면 false리턴
            else if(row == 1 && is_character(tokens[row][strlen(tokens[row]) - 1])) {
                if(strcmp(tokens[0], "extern") != 0 && strcmp(tokens[0], "unsigned") != 0 && is_typeStatement(tokens[0]) != 2)  
                    return false;
            }//토큰의 마지막이 문자일때 가장 처음의 토큰이 extern 또는 unsigned 일 경우 false 리턴
            else if(row > 1 && is_typeStatement(tokens[row - 1]) == 2){
                if(strcmp(tokens[row - 2], "unsigned") != 0 && strcmp(tokens[row - 2], "extern") != 0)
                    return false;
            }// 전 토큰이 명령어 일 때, 그 전의 토큰이 unsigned 또는 extern일때, false 리턴
        } 
    }


    if(row > 0)
    { //기존에 민들어진 토큰이 있을 때


        if(strcmp(tokens[0], "#include") == 0 || strcmp(tokens[0], "include") == 0 || strcmp(tokens[0], "struct") == 0){ 
            clear_tokens(tokens); 
            strcpy(tokens[0], remove_extraspace(str)); 
        }//토큰이 위와 같은 경우, str에서 빈칸을 지운 문자열을 토큰으로 만듬
    }
    //문자열이 명령어이거나, extern이 첫번째 토큰일 떄
    if(is_typeStatement(tokens[0]) == 2 || strstr(tokens[0], "extern") != NULL){
        for(i = 1; i < TOKEN_CNT; i++){
            if(strcmp(tokens[i],"") == 0)  
                break;             

            if(i != TOKEN_CNT -1 )
                strcat(tokens[0], " ");
            strcat(tokens[0], tokens[i]);
            memset(tokens[i], 0, sizeof(tokens[i]));
        }//0번 토큰 뒤에 i번 토큰을 붙이고 i번 토큰 초기화
    }


    while((p_str = find_typeSpecifier(tokens)) != -1){ 
        if(!reset_tokens(p_str, tokens))
            return false;
    } // 남은 문자열에 토큰으로 만들게 있으면 false리턴


    while((p_str = find_typeSpecifier2(tokens)) != -1){  
        if(!reset_tokens(p_str, tokens))
            return false;
    } // 남은 문자열에 토큰으로 만들게 있으면 false리턴

    return true;
}

node *make_tree(node *root, char (*tokens)[MINLEN], int *idx, int parentheses)
{ //토큰을 바탕으로 트리를 생성하는 함수
    node *cur = root;
    node *new;
    node *saved_operator;
    node *operator;
    int fstart;
    int i;

    while(1)    
    {
        if(strcmp(tokens[*idx], "") == 0)
            break;

        if(!strcmp(tokens[*idx], ")"))
            return get_root(cur);

        else if(!strcmp(tokens[*idx], ","))
            return get_root(cur);

        else if(!strcmp(tokens[*idx], "("))
        { //여는 괄호부터 닫는 괄호가 나올때 까지 내부로 트리를 만들어감

            if(*idx > 0 && !is_operator(tokens[*idx - 1]) && strcmp(tokens[*idx - 1], ",") != 0){
                fstart = true;
                //토큰이 연산자가 아니고 콤마가 아닐때
                while(1)
                {
                    *idx += 1;

                    if(!strcmp(tokens[*idx], ")"))
                        break;
                    //닫는 괄호가 나오면 종료
                    new = make_tree(NULL, tokens, idx, parentheses + 1);
                    //재귀호출로 자식노드들의 트리 생성
                    if(new != NULL){
                        if(fstart == true){
                            cur->child_head = new;
                            new->parent = cur;
                            //자식 노드 생성 후 부모 노드와 연결
                            fstart = false;
                        }
                        else{
                            cur->next = new;
                            new->prev = cur;
                        }

                        cur = new;
                    } //자식노드의 트리가 있을떄 형제 노드들을 생성함

                    if(!strcmp(tokens[*idx], ")"))
                        break; //닫는 괄호가 나오면 종료
                }
            }
            else{ //토큰이 연산자이거나 콤마일때
                *idx += 1;

                new = make_tree(NULL, tokens, idx, parentheses + 1);

                if(cur == NULL)
                    cur = new;

                else if(!strcmp(new->name, cur->name)){
                    if(!strcmp(new->name, "|") || !strcmp(new->name, "||") 
                            || !strcmp(new->name, "&") || !strcmp(new->name, "&&"))
                    { //and or 등의 연산자일떄
                        cur = get_last_child(cur);

                        if(new->child_head != NULL){
                            new = new->child_head;
                            //새로운 자식노드를 시작함
                            new->parent->child_head = NULL;
                            new->parent = NULL;
                            new->prev = cur;
                            cur->next = new;
                        }
                    }
                    else if(!strcmp(new->name, "+") || !strcmp(new->name, "*"))
                    { //더하기 또는 곱하기일때
                        i = 0;

                        while(1)
                        {
                            if(!strcmp(tokens[*idx + i], ""))
                                break;
                            //토큰이 공백이면 break
                            if(is_operator(tokens[*idx + i]) && strcmp(tokens[*idx + i], ")") != 0)
                                break;
                            //토큰이 닫는 괄호거나 연산자일 경우 break
                            i++;
                        }

                        if(get_precedence(tokens[*idx + i]) < get_precedence(new->name))
                        { //연산자의 우선순위를 고려하여 자식노드와 부모노드를 결정함
                            cur = get_last_child(cur);
                            cur->next = new;
                            new->prev = cur;
                            cur = new;
                        }
                        else
                        {
                            cur = get_last_child(cur);

                            if(new->child_head != NULL){
                                new = new->child_head;

                                new->parent->child_head = NULL;
                                new->parent = NULL;
                                new->prev = cur;
                                cur->next = new;
                            } //마지막 자식노드로 추가함
                        }
                    }
                    else{ //더하기나 곱하기가 아닐때
                        cur = get_last_child(cur);
                        cur->next = new;
                        new->prev = cur;
                        cur = new;
                    }
                }

                else
                { //새 노드와 현재 노드가 같은 문자일때
                    cur = get_last_child(cur);

                    cur->next = new;
                    new->prev = cur;

                    cur = new;
                }
            }
        }
        else if(is_operator(tokens[*idx]))
        { //토큰이 연산자일때
            if(!strcmp(tokens[*idx], "||") || !strcmp(tokens[*idx], "&&")
                    || !strcmp(tokens[*idx], "|") || !strcmp(tokens[*idx], "&") 
                    || !strcmp(tokens[*idx], "+") || !strcmp(tokens[*idx], "*"))
            {//토큰이 위와 같은 연산자일때
                if(is_operator(cur->name) == true && !strcmp(cur->name, tokens[*idx]))
                    operator = cur;
                    //현재 노드 저장
                else
                {
                    new = create_node(tokens[*idx], parentheses);
                    operator = get_most_high_precedence_node(cur, new);
                    //둘의 가장 상위 노드를 불러와 저장
                    if(operator->parent == NULL && operator->prev == NULL){
                        //연산자의 부모와 형제가 모두 없을떄
                        if(get_precedence(operator->name) < get_precedence(new->name)){
                            cur = insert_node(operator, new);
                        } //두 연산자의 우선순위를 비교하여 새 노드 삽입

                        else if(get_precedence(operator->name) > get_precedence(new->name))
                        {
                            if(operator->child_head != NULL){
                                operator = get_last_child(operator);
                                cur = insert_node(operator, new);
                            }
                        }//연산자 우선순위를 비교하여 자식노드의 마지막에 새 노드 생성
                        else
                        {
                            operator = cur;

                            while(1)
                            {
                                if(is_operator(operator->name) == true && !strcmp(operator->name, tokens[*idx]))
                                    break;
                                //operator가 토큰과 같아지면 탈출
                                if(operator->prev != NULL)
                                    operator = operator->prev;
                                else
                                    break;
                            }//operator의 마지막 형제 노드까지 이동하고 루프 탈출

                            if(strcmp(operator->name, tokens[*idx]) != 0)
                                operator = operator->parent;
                            //토큰과 operator가 같지 않다면 부모노드로 이동
                            if(operator != NULL){
                                if(!strcmp(operator->name, tokens[*idx]))
                                    cur = operator;
                            }//연산자가 null이 아니고 토큰과 같을떄 현재 노드를 operator로 덮어씀
                        }
                    }

                    else
                        cur = insert_node(operator, new);
                }//연산자의 부모 현제노드가 없는 경우가 아닐 경우 새 노드 생성 후 트리에 추가함

            }
            else
            {//토큰이 위와 같은 연산자가 아닐때
                new = create_node(tokens[*idx], parentheses);

                if(cur == NULL)
                    cur = new;

                else
                {
                    operator = get_most_high_precedence_node(cur, new);
                    //현재 노드중 최상위 노드를 불러옴
                    if(operator->parentheses > new->parentheses)
                        cur = insert_node(operator, new);

                    else if(operator->parent == NULL && operator->prev ==  NULL){
                        //operator의 부모 형제 노드 모두 없을때
                        if(get_precedence(operator->name) > get_precedence(new->name))
                        { //연산자 순위 비교
                            if(operator->child_head != NULL){

                                operator = get_last_child(operator);
                                cur = insert_node(operator, new);
                            }//operator의 자식노드가 있는 경우 자식노드의 가장 마지막에 추가함
                        }

                        else    
                            cur = insert_node(operator, new);
                    }//operator의 prev에 새노드 추가

                    else
                        cur = insert_node(operator, new);
                } //operator의 prev에 새노드 추가
            }
        }
        else //토큰이 여는 괄호가 아니고 연산자도 아닐때
        {
            new = create_node(tokens[*idx], parentheses);
            //새 노드 생성
            if(cur == NULL)
                cur = new;
            //현재 노드가 없을 경우 현재노드가 됨
            else if(cur->child_head == NULL){
                cur->child_head = new;
                new->parent = cur;

                cur = new;
            } //현재노드의 자식만 없을 경우 자식 노드가 됨
            else{
                //그 외의 경우 마지막 자식노드의 prev 노드가 됨
                cur = get_last_child(cur);

                cur->next = new; //왼쪽 노드
                new->prev = cur; //오른쪽 노드

                cur = new;
            }
        }

        *idx += 1;
    }//다음 토큰으로 이동

    return get_root(cur);
}//루트를 리턴함

node *change_sibling(node *parent)
{ //자식 노드의 순서를 바꾸는 함수
    node *tmp;

    tmp = parent->child_head;
    //원래의 child_head 저장
    parent->child_head = parent->child_head->next;
    parent->child_head->parent = parent;
    parent->child_head->prev = NULL;
    //원래의 child_head의 next를 새 child_head로 지정
    parent->child_head->next = tmp;
    parent->child_head->next->prev = parent->child_head;
    parent->child_head->next->next = NULL;
    parent->child_head->next->parent = NULL;        
    //새 child_head의 next를 원래의 child_head로 지정
    return parent;
}

node *create_node(char *name, int parentheses)
{ //트리의 노드를 새로 생성하는 함수
    node *new;

    new = (node *)malloc(sizeof(node));
    new->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new->name, name);

    new->parentheses = parentheses;
    new->parent = NULL;
    new->child_head = NULL;
    new->prev = NULL;
    new->next = NULL;

    return new;
}

int get_precedence(char *op)
{ //지정한 연산자 우선순위를 검색함
    int i;

    for(i = 2; i < OPERATOR_CNT; i++){
        if(!strcmp(operators[i].operator, op))
            return operators[i].precedence;
    }
    return false;
} //찾은 연산자 우선순위를 반환함

int is_operator(char *op)
{ //입력된 문자가 연산자인지 확인하는 함수
    int i;

    for(i = 0; i < OPERATOR_CNT; i++)
    {
        if(operators[i].operator == NULL)
            break;
        if(!strcmp(operators[i].operator, op)){
            return true;
        }
    }
    return false;
}

void print(node *cur)
{ //트리를 하나씩 출력하는 함수
    if(cur->child_head != NULL){
        print(cur->child_head);
        printf("\n");
    }

    if(cur->next != NULL){
        print(cur->next);
        printf("\t");
    }
    printf("%s", cur->name);
}

node *get_operator(node *cur)
{ // 트리  탐색중 연산자를 불러오기 위한 함수
    if(cur == NULL)
        return cur;

    if(cur->prev != NULL)
        while(cur->prev != NULL)
            cur = cur->prev;

    return cur->parent;
} //child_head의 부모노드는 연산자이므로 이를 반환함

node *get_root(node *cur)
{ // 트리 탐색중 root 노드를 확인하기 위한 함수
    if(cur == NULL)
        return cur;

    while(cur->prev != NULL)
        cur = cur->prev;

    if(cur->parent != NULL)
        cur = get_root(cur->parent);

    return cur;
} //루트 노드에 닿을때까지 반복한다

node *get_high_precedence_node(node *cur, node *new)
{ //상위에 있는 노드를 탐색하기 위한 함수
    if(is_operator(cur->name))
        if(get_precedence(cur->name) < get_precedence(new->name))
            return cur;

    if(cur->prev != NULL){
        while(cur->prev != NULL){
            cur = cur->prev;

            return get_high_precedence_node(cur, new);
        }
        //가장 상단에 도착할 떄까지 재귀 순환

        if(cur->parent != NULL)
            return get_high_precedence_node(cur->parent, new);
    }

    if(cur->parent == NULL)
        return cur;
}

node *get_most_high_precedence_node(node *cur, node *new)
{ //가장 상위에 있는 노드를 탐색하기 위한 함수
    node *operator = get_high_precedence_node(cur, new);
    node *saved_operator = operator;

    while(1)
    {
        if(saved_operator->parent == NULL)
            break;

        if(saved_operator->prev != NULL)
            operator = get_high_precedence_node(saved_operator->prev, new);

        else if(saved_operator->parent != NULL)
            operator = get_high_precedence_node(saved_operator->parent, new);

        saved_operator = operator;
    } //get_high_precedence_node() 함수를 재귀적으로 호출하여 최상위의 노드를 탐색함

    return saved_operator;
}

node *insert_node(node *old, node *new)
{ // 트리에 새 노드를 추가하는 함수
    if(old->prev != NULL){
        new->prev = old->prev;
        old->prev->next = new;
        old->prev = NULL;
    }

    new->child_head = old;
    old->parent = new;

    return new;
}

node *get_last_child(node *cur)
{ //노드의 가장 마지막 자식 노드를 탐색하는 함수
    if(cur->child_head != NULL)
        cur = cur->child_head;

    while(cur->next != NULL)
        cur = cur->next;

    return cur;
}

int get_sibling_cnt(node *cur)
{ //자식노드의 총 갯수를 탐색하는 함수
    int i = 0;

    while(cur->prev != NULL)
        cur = cur->prev;

    while(cur->next != NULL){
        cur = cur->next;
        i++;
    }

    return i;
} //형제 노드의 가장 마지막에서부터 head로 오면서 갯수를 셈

void free_node(node *cur)
{ //트리를 만들면서 지정한 메모리를 free 해주는 함수
    if(cur->child_head != NULL)
        free_node(cur->child_head);
    //자식 노드가 있는 경우 자식노드 해제
    if(cur->next != NULL)
        free_node(cur->next);
    //형제 노드가 있는 경우 형제노드 해제
    if(cur != NULL){
        cur->prev = NULL;
        cur->next = NULL;
        cur->parent = NULL;
        cur->child_head = NULL;
        free(cur);
    }
} //트리 전체를 순환하며 남는 것이 없게 메모리를 해제해줌


int is_character(char c)
{ //문자인지 확인하는 함수
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_typeStatement(char *str)
{ //명령어를 구분해 내는 함수
    char *start;
    char str2[BUFLEN] = {0}; 
    char tmp[BUFLEN] = {0}; 
    char tmp2[BUFLEN] = {0}; 
    int i;   

    start = str;
    strncpy(str2,str,strlen(str));
    remove_space(str2);

    while(start[0] == ' ')
        start += 1;
    //gcc 명령어가 포함되어있을 경우
    if(strstr(str2, "gcc") != NULL)
    {
        strncpy(tmp2, start, strlen("gcc"));
        if(strcmp(tmp2,"gcc") != 0)
            return 0;
        else
            return 2;
    }//start에서 tmp2로 3개만큼 문자열 복사

    for(i = 0; i < DATATYPE_SIZE; i++)
    {
        if(strstr(str2,datatype[i]) != NULL)
        {   
            strncpy(tmp, str2, strlen(datatype[i]));
            strncpy(tmp2, start, strlen(datatype[i]));
            //문자열을 tmp, tmp2로 지정한 문자열의 길이만큼 복사
            if(strcmp(tmp, datatype[i]) == 0)
                if(strcmp(tmp, tmp2) != 0)
                    return 0;  
                else
                    return 2;
        } //복사한 문자열들을 비교 판단함

    }
    return 1;

}

int find_typeSpecifier(char tokens[TOKEN_CNT][MINLEN]) 
{ //문자의 type을 결정하는 인자를 추출하는 함수
    int i, j;

    for(i = 0; i < TOKEN_CNT; i++)
    {
        for(j = 0; j < DATATYPE_SIZE; j++)
        {
            if(strstr(tokens[i], datatype[j]) != NULL && i > 0)
            {
                if(!strcmp(tokens[i - 1], "(") && !strcmp(tokens[i + 1], ")") 
                        && (tokens[i + 2][0] == '&' || tokens[i + 2][0] == '*' 
                            || tokens[i + 2][0] == ')' || tokens[i + 2][0] == '(' 
                            || tokens[i + 2][0] == '-' || tokens[i + 2][0] == '+' 
                            || is_character(tokens[i + 2][0])))  
                    return i;
            }
        }
    }
    return -1;
}

int find_typeSpecifier2(char tokens[TOKEN_CNT][MINLEN]) 
{ //변수의 type을 결정하는 인자를 추출해내는 함수
    int i, j;

    for(i = 0; i < TOKEN_CNT; i++)
    {
        for(j = 0; j < DATATYPE_SIZE; j++)
        {
            if(!strcmp(tokens[i], "struct") && (i+1) <= TOKEN_CNT && is_character(tokens[i + 1][strlen(tokens[i + 1]) - 1]))  
                return i;
        }
    }
    return -1;
}

int all_star(char *str)
{ // 문자열이 모두 *인지 확인하는 함수
    int i;
    int length= strlen(str);

    if(length == 0) 
        return 0;

    for(i = 0; i < length; i++)
        if(str[i] != '*')
            return 0;
    return 1;

}

int all_character(char *str)
{ //문자열이 모두 문자인지 확인하는 힘수
    int i;

    for(i = 0; i < strlen(str); i++)
        if(is_character(str[i]))
            return 1;
    return 0;

}

int reset_tokens(int start, char tokens[TOKEN_CNT][MINLEN]) 
{ //분해한 토큰을 다시 하나의 문자열로 합치는 함수
    int i;
    int j = start - 1;
    int lcount = 0, rcount = 0;
    int sub_lcount = 0, sub_rcount = 0;

    if(start > -1){
        if(!strcmp(tokens[start], "struct")) {      
            strcat(tokens[start], " ");
            strcat(tokens[start], tokens[start+1]);      

            for(i = start + 1; i < TOKEN_CNT - 1; i++){
                strcpy(tokens[i], tokens[i + 1]);
                memset(tokens[i + 1], 0, sizeof(tokens[0]));
            }
        }

        else if(!strcmp(tokens[start], "unsigned") && strcmp(tokens[start+1], ")") != 0) {      
            strcat(tokens[start], " ");
            strcat(tokens[start], tokens[start + 1]);        
            strcat(tokens[start], tokens[start + 2]);

            for(i = start + 1; i < TOKEN_CNT - 1; i++){
                strcpy(tokens[i], tokens[i + 1]);
                memset(tokens[i + 1], 0, sizeof(tokens[0]));
            }
        }

        j = start + 1;           
        while(!strcmp(tokens[j], ")")){
            rcount ++;
            if(j==TOKEN_CNT)
                break;
            j++;
        }

        j = start - 1;
        while(!strcmp(tokens[j], "(")){
            lcount ++;
            if(j == 0)
                break;
            j--;
        }
        if( (j!=0 && is_character(tokens[j][strlen(tokens[j])-1]) ) || j==0)
            lcount = rcount;

        if(lcount != rcount )
            return false;

        if( (start - lcount) >0 && !strcmp(tokens[start - lcount - 1], "sizeof")){
            return true; 
        }

        else if((!strcmp(tokens[start], "unsigned") || !strcmp(tokens[start], "struct")) && strcmp(tokens[start+1], ")")) {     
            strcat(tokens[start - lcount], tokens[start]);
            strcat(tokens[start - lcount], tokens[start + 1]);
            strcpy(tokens[start - lcount + 1], tokens[start + rcount]);

            for(int i = start - lcount + 1; i < TOKEN_CNT - lcount -rcount; i++) {
                strcpy(tokens[i], tokens[i + lcount + rcount]);
                memset(tokens[i + lcount + rcount], 0, sizeof(tokens[0]));
            }


        }
        else{
            if(tokens[start + 2][0] == '('){
                j = start + 2;
                while(!strcmp(tokens[j], "(")){
                    sub_lcount++;
                    j++;
                }   
                if(!strcmp(tokens[j + 1],")")){
                    j = j + 1;
                    while(!strcmp(tokens[j], ")")){
                        sub_rcount++;
                        j++;
                    }
                }//괄호의 갯수를 맞추기 위해 여는 괄호와 닫는 괄호의 갯수를 계산함
                else 
                    return false;

                if(sub_lcount != sub_rcount)
                    return false;

                strcpy(tokens[start + 2], tokens[start + 2 + sub_lcount]);  
                for(int i = start + 3; i<TOKEN_CNT; i++)
                    memset(tokens[i], 0, sizeof(tokens[0]));

            }
            strcat(tokens[start - lcount], tokens[start]);
            strcat(tokens[start - lcount], tokens[start + 1]);
            strcat(tokens[start - lcount], tokens[start + rcount + 1]);

            for(int i = start - lcount + 1; i < TOKEN_CNT - lcount -rcount -1; i++) {
                strcpy(tokens[i], tokens[i + lcount + rcount +1]);
                memset(tokens[i + lcount + rcount + 1], 0, sizeof(tokens[0]));

            }
        }
    }
    return true;
}

void clear_tokens(char tokens[TOKEN_CNT][MINLEN])
{
    int i;

    for(i = 0; i < TOKEN_CNT; i++)
        memset(tokens[i], 0, sizeof(tokens[i]));
} //토큰들을 모두 널문자로 초기화 하는 함수

char *rtrim(char *_str)
{// 문자열의 뒤쪽부터 공백이 나올때까지 자르고 나머지를 리턴하는 함수
    char tmp[BUFLEN];
    char *end;

    strcpy(tmp, _str);
    end = tmp + strlen(tmp) - 1;
    while(end != _str && isspace(*end))
        --end;

    *(end + 1) = '\0';
    _str = tmp;
    return _str;
}

char *ltrim(char *_str)
{// 문자열의 앞쪽부터 공백이 나올때까지 자르고 나머지를 리턴하는 함수
    char *start = _str;

    while(*start != '\0' && isspace(*start))
        ++start;
    _str = start;
    return _str;
}

char* remove_extraspace(char *str)
{ //문자열에 공백이 1개 이상 연속될 때, 1개만 남기고 공백을 지우는 함수
    int i;
    char *str2 = (char*)malloc(sizeof(char) * BUFLEN);
    char *start, *end;
    char temp[BUFLEN] = "";
    int position;

    if(strstr(str,"include<")!=NULL){
        start = str;
        end = strpbrk(str, "<");
        position = end - start;

        strncat(temp, str, position);
        strncat(temp, " ", 1);
        strncat(temp, str + position, strlen(str) - position + 1);

        str = temp;     
    } //문자열의 시작이 include 일 경우 뒤에 오는 헤더파일을 구분하기 위해 문자열을 자름

    for(i = 0; i < strlen(str); i++)
    {
        if(str[i] ==' ')
        {
            if(i == 0 && str[0] ==' ')
                while(str[i + 1] == ' ')
                    i++;    
            else{
                if(i > 0 && str[i - 1] != ' ')
                    str2[strlen(str2)] = str[i];
                while(str[i + 1] == ' ')
                    i++;
            } 
        } //문자열 중간에 있는 공백을 제거함
        else
            str2[strlen(str2)] = str[i];
    }

    return str2;
}



void remove_space(char *str)
{ //문자열의 공백을 제거하는 함수
    char* i = str;
    char* j = str;

    while(*j != 0)
    {
        *i = *j++;
        if(*i != ' ')
            i++;
    }//공백문자를 뛰어넘는 방식으로 공백을 없앰
    *i = 0;
}

int check_brackets(char *str)
{ //여는괄호 닫는 괄호 갯수가 일치하는지 확인하는 함수
    char *start = str;
    int lcount = 0, rcount = 0;

    while(1){
        if((start = strpbrk(start, "()")) != NULL){
            if(*(start) == '(')
                lcount++;
            else
                rcount++;

            start += 1;         
        }
        else
            break;
    }

    if(lcount != rcount)
        return 0;
    else 
        return 1;
} 

int get_token_cnt(char tokens[TOKEN_CNT][MINLEN])
{ //토큰의 갯수를 세는 함수
    int i;

    for(i = 0; i < TOKEN_CNT; i++)
        if(!strcmp(tokens[i], ""))
            break;

    return i;
}

