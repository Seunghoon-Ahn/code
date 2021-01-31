#include <stdio.h>
#include <stdlib.h>

int a, b; 

void menu(void);
int plus(int, int);
int sub(int, int);
int multi(int, int);
double _div(int, int);
_Bool compare(int, int);
void return_end(void);

void menu(void){
	printf("\n[1. 두 수의 값 초기화]\n[2. PLUS]\n[3.SUB]\n[4.MULTI]\n[5. DIV]\n[6. 두수의 합 짝수 / 홀수 비교]\n[7. PROGRAM END]\n");
}

int plus(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return a-b;
}

int multi(int a, int b){
	return a * b;
}

double _div(int a, int b){
	return (double)a / b;
}

void return_end(void){
	char botton;
	printf("Y: return Manu/ N: program end\n>");
	getchar();
	scanf("%c", &botton);
	
	if(botton != 'Y')
		exit(1);
}

_Bool compare(int a, int b){
	if(plus(a, b) % 2 == 0)
		return 1;
	else
		return 0;
}


int main(void){
	int button;
	int a = 0, b = 0;

	while(1){
		system("clear");
		menu();
		printf("현재 a : %d, b : %d\n", a, b);
		printf("SELECT MANU>");
		scanf("%d", &button);
		switch(button){
			case 1:
				printf("\n두 수의 값을 초기화해 주세요.\n>");
				scanf("%d %d", &a, &b);
				break;
			case 2:
			   	printf("\nRESULT:\n");	
				printf("두 수의 합은 %d 입니다.\n", plus(a, b));			   
				return_end();
				break;
			case 3:
				printf("\nRESULT:\n");
				printf("두 수의 차는 %d 입니다.\n", sub(a, b));
				return_end();
				break;
			case 4:
				printf("\nRESULT:\n");
				printf("두 수의 곱은 %d 입니다.\n", multi(a, b));
				return_end();
				break;
			case 5:
				printf("\nRESULT:\n");
				printf("두 수의 나눗셈의 몫은 %f 입니다.\n", _div(a, b));
				return_end();
				break;
			case 6:
				if(compare(a, b) == 1)
					printf("두 수의 합은 짝수입니다.\n");
				else
					printf("두 수의 합은 홀수입니다.\n");
				return_end();
				break;
			case 7:
				printf("\n프로그램 종료\n");
				exit(1);
				break;
		}
	}
}
