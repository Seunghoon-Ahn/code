#include <stdio.h>
#include <stdlib.h>

#define BUFFER_MAX 256

int main(void)
{
	char command[BUFFER_MAX];
	char *prompt = "Prompt>>";
	//프롬프트 형식을 만들기 위한 문자열 생성
	while(1) {
		fputs(prompt, stdout);
		//프롬프트 형식 출력
		if(fgets(command, sizeof(command), stdin) == NULL)
			break;//입력된게 없는 경우 break
		//사용자로부터 표준입력으로 command를 입력받음
		system(command); //command를 system으로 입력
	}
	fprintf(stdout, "Good bye...\n"); //종료시 종료 문구 출력
	fflush(stdout); //표준 출력 비우기
	exit(0); //프로그램 종료
}

