#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void) {
	char buf[BUFFER_SIZE];
	int length;
	
	length = read(0, buf, BUFFER_SIZE);
	//read함수로 표준 입력에서 데이터를 읽어옴
	//읽어온 길이를 read의 리턴값으로 알아내여 변수 length에 저장함
	write(1, buf, length);
	//표준 출력에 write함수를 이용하여 출력함
	exit(0);
}

