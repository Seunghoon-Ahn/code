#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void ssu_timestamp(char *str);

int main(void)
{
	unsigned int ret;

	ssu_timestamp("before sleep()"); //현재시간 출력
	ret = sleep(10); //100초 슬립
	ssu_timestamp("after stamp()"); //현재시간 출력
	printf("sleep() returned %d\n", ret); //sleep의 리턴값 출력
	exit(0);
}

void ssu_timestamp(char *str) {
	time_t time_val;
	time(&time_val); //현재시간 받아옴
	printf("%s the time is %s\n", str, ctime(&time_val)); //현재시간 출력
}
