#ifndef BLANK_H_
#define BLANK_H_

#ifndef true
	#define true 1
#endif
#ifndef false
	#define false 0
#endif
#ifndef BUFLEN
	#define BUFLEN 1024
#endif

#define OPERATOR_CNT 24
#define DATATYPE_SIZE 35
#define MINLEN 64
#define TOKEN_CNT 50

typedef struct node{
		int parentheses;
		char *name;
		struct node *parent;
		struct node *child_head;
		struct node *prev;
		struct node *next;
}node; //트리를 구성하기 위한 노드 구조체

typedef struct operator_precedence{
		char *operator;
			int precedence;
}operator_precedence; //연산자의 우선순위를 저장하는 구조체

void compare_tree(node *root1,  node *root2, int *result);
//두개의 트리를 서로 비교하는 함수
node *make_tree(node *root, char (*tokens)[MINLEN], int *idx, int parentheses);
//토큰을 바탕으로 트리를 생성하는 함수
node *change_sibling(node *parent);
//트리의 형제 노드(같은 레벨의 노드)를 서로 교환하는 함수
node *create_node(char *name, int parentheses);
// 노드를 새로 생성하는 함수
int get_precedence(char *op);
//연산자의 우선순위를 결정하는 함수
int is_operator(char *op);
// 주어진 문자가 연산자인지 확인하는 함수
void print(node *cur);
//트리를 순환하면 출력하는 함수
node *get_operator(node *cur);
//트리 탐색 중 연산자를 구분하는 함수
node *get_root(node *cur);
//트리 탐색 중 root노드를 탐색하기 위한 함수
node *get_high_precedence_node(node *cur, node *new);
// 두 노드 중 더 높은 우선순위의 노드를 계산하는 함수
node *get_most_high_precedence_node(node *cur, node *new);
// 가장 우선순위가 높은 노드를 구분하는 함수
node *insert_node(node *old, node *new);
// 트리에 새로 노드를 삽입하기 위한 함수
node *get_last_child(node *cur);
//노드의 가장 마지막 자식 노드를 탐색하는 함수
void free_node(node *cur);
//트리를 위해 지정한 메모리를 해제해주는 함수
int get_sibling_cnt(node *cur);
//형제 노드의 총 개수를 계산하는 함수
int make_tokens(char *str, char tokens[TOKEN_CNT][MINLEN]);
// 학생의 정답과 정답지의 정답을 토큰으로 분해할 때 사용하는 함수
int is_typeStatement(char *str);
//명령어를 구분하는 함수
int find_typeSpecifier(char tokens[TOKEN_CNT][MINLEN]);
//문자의 type을 결정하는 인자를 추출하는 함수
int find_typeSpecifier2(char tokens[TOKEN_CNT][MINLEN]);
//변수의 type을 결정하는 인자를 추출해내는 함수
int is_character(char c);
// 문자인지 확인하는 함수
int all_star(char *str);
//문자열이 모두 *문자인지 확인하는 함수
int all_character(char *str);
//문자열이 모두 문자로 이루어져 있는지 확인하는 함수
int reset_tokens(int start, char tokens[TOKEN_CNT][MINLEN]);
//분해한 토큰을 다시 문자열로 합치는 함수
void clear_tokens(char tokens[TOKEN_CNT][MINLEN]);
//모든 토큰을 널문자로 초기화하는 함수
int get_token_cnt(char tokens[TOKEN_CNT][MINLEN]);
// NULL문자가 아닌 토큰의 개수를 세는 함수
char *rtrim(char *_str);
//문자열의 뒤쪽부터 공백이 나올때까지 자르고 나머지를 리턴하는 함수
char *ltrim(char *_str);
//문자열의 앞쪽부터 공백이 나올때까지 자르고 나머지를 리턴하는 함수
void remove_space(char *str);
//문자열의 공백을 제거하는 함수
int check_brackets(char *str);
//여는 괄호와 닫는 괄호의 개수가 일치하는지 확인하는 함수
char* remove_extraspace(char *str);
//문자열에 공백이 1개 이상 연속될 때, 1개만 남기고 공백을 제거하는 함수


#endif

