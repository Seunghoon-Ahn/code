#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
	char operator;
	FILE *fp;
	int character;
	int number = 0;

	if((fp = fopen("ssu_expr.txt", "r")) == NULL) {
		fprintf(stderr, "fopen error for ssu_expr.txt\n");
		exit(1);
	} //fp에 ssu_expr.txt 파일을 오픈함, 실패시 에러 출력 후 종료

	while(!feof(fp)) { //fp가 파일의 끝이 아닐때
		while((character = fgetc(fp)) != EOF && isdigit(character))
			number = 10 * number + character - 48;
		//한 문자를 읽어온 것이 숫자일 경우, 숫자로 만들어서 number에 저장
		fprintf(stdout, " %d\n", number);//연산자를 만나면 숫자 출력
		number = 0; //숫자 초기화

		if(character != EOF) { //한 문자 읽어온것이 파일의 끝이 아니라면
			ungetc(character, fp); //읽어온 한 문자를 반환함(연산자)
			operator = fgetc(fp); //ungetc가 반환한 문자를 다시 읽어옴
			printf("Operator=> %c\n", operator); //연산자 표시하여 문자 출력
		}
	}
	fclose(fp); //파일 닫음
	exit(0); //프로그램 종료
}

