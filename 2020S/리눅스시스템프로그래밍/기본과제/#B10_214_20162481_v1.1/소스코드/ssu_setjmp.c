#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register);

static jmp_buf glob_buffer;

int main(void)
{
	register int loc_register;
	volatile int loc_volatile;
	int loc_var;

	loc_var = 10;
	loc_volatile = 11;
	loc_register = 12;

	if(setjmp(glob_buffer) != 0) { //lonjmp로 돌아올 위치 설정
		printf("after longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
		exit(0);
	}
	//최적화 옵션을 사용하지 않으면 변수들이 메모리에 저장됨
	loc_var = 80;
	loc_volatile = 81;
	loc_register = 83;
	ssu_nested_func(loc_var, loc_volatile, loc_register);
	//변수가 메모리에 저장되어있어 값을 유지함
	exit(0);
}

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register) {
	printf("before longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
	longjmp(glob_buffer, 1); //setjmp로 이동
} //최적화 옵션 사용시 지역변수와 register 변수는 register에 저장됨
