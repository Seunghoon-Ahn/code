#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

void play(char **tokens);

char **tokenize(char *line) { //입려된 문장을 토큰으로 분해하는 함수
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

	for(i =0; i < strlen(line); i++){
		char readChar = line[i];
		if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
			token[tokenIndex] = '\0';
			if (tokenIndex != 0){
				tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0; 
				}
		} 
		else {
			token[tokenIndex++] = readChar;
		}
	}

	free(token);
	tokens[tokenNo] = NULL;
	return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;

	FILE* fp;
	if(argc == 2) {
		fp = fopen(argv[1],"r");
		if(fp < 0) {
			printf("File doesn't exists.");
			return -1;
		}
	} //배치식 모드와 사용자 입력 모드를 구분

	char curdir[1024] = {0, };
	getcwd(curdir, 1024);
	//realpath(".", curdir);
	char for_env[1024] = {0, };
	strcpy(for_env, getenv("PATH"));
	strcat(for_env, ":");
	strcat(for_env, curdir);
	setenv("PATH", for_env, 1); //PATH 환경 변수에 현재 디렉토리 추가

	while(1) {          
		/* BEGIN: TAKING INPUT */
		//bzero(line, sizeof(line));
		memset(line, 0, sizeof(line));
		if(argc == 2) { // batch mode
			if(fgets(line, sizeof(line), fp) == NULL) { // file reading finished
				break;  
			}
			line[strlen(line) - 1] = '\0'; //배치식 모드일때 파일에서 한 줄씩 읽어옴
		} else { // interactive mode
			printf("$ ");
			scanf("%[^\n]", line);
			getchar();
		} //명령문 입력모드일때는 쉘에서 명령어를 입력받음

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line); //입력된 문장을 토큰으로 분해

		play(tokens); //토큰을 이용하여 문장 실행

		// Freeing the allocated memory 
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens); //동적할당 되어있던 토큰의 메모리 해제

	}
	return 0;
}

void play(char** tokens) { //명령어를 실행하는 함수
	char path[MAX_INPUT_SIZE];
	pid_t pid;
	int check = 0;
	int pipe_fd[2];
	int pipenum = 0;
	int i = 0, tmp = 1;
	int pipeloc[35];
	int status;
	memset(pipeloc, 0, sizeof(pipeloc));

	for(i = 0; tokens[i] != NULL; i++) {
		if(!strcmp(tokens[i], "|")) {
			pipenum++;
			tokens[i] = NULL;
			pipeloc[tmp++] = i + 1;
		}
	} //파이프의 위치를 찾아서 파이프를 NULL로 바꾼 뒤, 파이프의 위치 저장

	int cnt = 0;
	int fd_tmp = 0;
	while(cnt <= pipenum) { //명령어 갯수 만큼 반복
		pipe(pipe_fd); //파이프 설정
		if((pid = fork()) < 0) { //fork를 통해 자식 프로세스에서 명령문을 실행
			fprintf(stderr, "fork error\n");
			exit(1);
		}
		else if (pid == 0) { //자식 프로세스일때
			dup2(fd_tmp, 0);
			if(cnt < pipenum) {
				dup2(pipe_fd[1], 1);
				close(pipe_fd[0]);
			}
			memset(path, 0, sizeof(path));
			strcat(path, *(tokens + pipeloc[cnt]));
			check = execvp(path, tokens + pipeloc[cnt]); //execvp 함수를 이용하여 명령어 + 조건문으로 실행함

			if(check == -1) { //부모 프로세스 일때
				printf("SSUShell : Incorrect command\n");
				exit(1);
				break;
			}           
		}
		else { //부모 프로세스 일때
			wait(&status);
			close(pipe_fd[1]);
			fd_tmp = pipe_fd[0];
			cnt++;
		}
	}
	return; 
}