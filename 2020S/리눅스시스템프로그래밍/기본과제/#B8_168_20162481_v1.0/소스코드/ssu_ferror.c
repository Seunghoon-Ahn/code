#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int character;

	if(argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}//사용자가 인자를 잘못 입력하였을 경우 에러 출력 후 종료
	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}//파일을 fp에 오픈함, 실패시 오류 출력 후 종료
	
	character = fgetc(fp);
	//파일에서 한글자를 읽어옴
	while(!feof(fp)) { //파일의 끝이 아닐 경우
		fputc(character, stdout);
		//fputc() 함수를 통해 한문자를 표준 출력으로 출력함
		if(ferror(fp)) { //에러 발생시 에러 메시지 출력
			fprintf(stderr, "Error detected!\n");
			clearerr(fp);
		}
		//파일에서 한문자를 읽어옴
		character = fgetc(fp);
	}

	fclose(fp); //파일을 저장하고 종료함
	exit(0); // 프로그램 종료
}

