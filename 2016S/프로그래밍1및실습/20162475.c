#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define leapyear(year) ((year)%4==0 && ((year)%100!=0 || (year)%400==0))
#include <math.h>
#define MAX 100


int main();



//달력함수//

void calender(int year, int month, char schedule_storage[100][13][32][10]){			
	int e_date[]={0,31,28,31,30,31,30,31,31,30,31,30,31};                           			//각 월별 마지막 날짜        
	int l_year,day;
	int i,j,k;

	/* 윤년 판정*/
	if(month == 2 && leapyear(year))
	{
		e_date[2]=29;
	}


	l_year=year-1;																					//올해의 시작 날짜를 작년의 시작날짜와 비교

	/* 그 달의 시작 날짜를 설정*/
	day = (l_year+(l_year/4)-(l_year/100)+(l_year/400)+1)%7;										

	for(i=1;i < month;i++)														
	{
		day += e_date[i];
	}
	day%=7;


	/*달력 출력*/
	printf("\n                           %d년  %d월",year+2000,month);
	printf("\n       Sun.     Mon.    Tues.     Wed.    Thrus.    Fri.    Sat.\n");


	if(leapyear(year) && month>2)                                                           //윤년일 시 3월부터 날짜를 한칸씩 뒤로 밈
	{
		for(i=-day;i<e_date[month]+1;i++)
		{
			if((i+day)%7==0)                                                                //토~일로 넘어가는 구간에서 개행
			{
				printf("\n\n");
				if(i<=0)
				{
					printf("\n\n\n\n");
				}
				else
				{
					for(j=i-7;j<i;j++)														//스케줄이 있을 시 스케줄을 출력
					{
						if(schedule_storage[year][month][j]==0)                             
						{
							printf("         ");
						}

						else
						{
							printf("%9s",schedule_storage[year][month][j]);
						}
					}
					printf("\n\n\n");
				}
			}

			if(i<=0)
			{
				printf("         ");
			}
			else
			{
				printf("%9d",i);

			}
		}
		printf("\n\n");

		for(i=e_date[month]-4;i<e_date[month]+3;i++)
		{
			if(schedule_storage[year][month][i]==0)
			{
				printf("         ");
			}
			else
			{
				printf("%9s",schedule_storage[year][month][i]);

			}
		}
		printf("\n\n\n");
	}
	else                                                                                    //평년시 달력 출력(그 외에는 위와 같은 식)
	{
		for(i=-day;i<e_date[month];i++)
		{
			if((i+day)%7==0)
			{
				printf("\n\n");

				if(i<=0)
				{
					printf("\n\n\n\n");
				}
				else
				{
					for(j=i-6;j<i+1;j++)
					{
						if(schedule_storage[year][month][j]==0)
						{
							printf("         ");
						}
						else
							printf("%9s",schedule_storage[year][month][j]);
					}
					printf("\n\n\n");

				}
			}
			if(i<0)
			{
				printf("         ");
			}
			else
			{
				printf("%9d",i+1);
			}
		}
		printf("\n\n");

		for(i=e_date[month]-5;i<e_date[month]+2;i++)
		{
			if(schedule_storage[year][month][i]==0)

			{
				printf("         ");
			}
			else
			{
				printf("%9s",schedule_storage[year][month][i]);

			}
		}
		printf("\n\n\n");
	}
	getchar();
	getchar();
	system("clear");                                                                       //엔터를 누르면 clear

}

/*일정 입력시 정보를 주는 함수*/

void s_input(int year,int month,int date,char schedule[]){

	printf("출력 : %d년 %d월 %d일 %s",year+2000,month,date,schedule);
	printf("\n일정을 추가하였습니다.\n아무키나 입력하세요..........");
	getchar();
	getchar();
	system("clear");
}

/*일정 중복시 정보를 주는 함수*/
int over(int year, int month, int date, char schedule[]){
	char yon;
	printf("출력 : %d년 %d월 %d일 %s",year+2000,month,date,schedule);
	printf("\n%d년 %d월 %d일에 일정이 있습니다.\n일정을 덮어쓰시려면 Y를, 취소하려면 N을 입력하세요 : ",year+2000,month,date);
	getchar();
	scanf("%c",&yon);
	if(yon== 'y')																					//덮어 쓸 경우
	{
		printf("\n일정을 추가하였습니다.\n아무키나 입력하세요.........");
		getchar();
		getchar();
		system("clear");
		return 1;
	}
	else if(yon == 'n')																				//취소 할 경우
	{
		system("clear");
	}
	else																							//그 외의 경우
	{
		printf("잘못된 입력입니다\n아무키나 입력하세요.........");
		system("clear");
		getchar();
		getchar();
	}
}

/*일정 삭제 하는 함수*/

void delete_1(int year, int month, int date){														//일정이 있던 경우
	year+=2000;
	printf("%d년 %d월 %d일에 일정이 있습니다.\n일정을 삭제하였습니다.\n아무키나 입력하세요.........",year,month,date);
	getchar();
	getchar();
	system("clear");
}


void delete_0(int year, int month, int date){														//일정이 없던 경우
	year+=2000;
	printf("%d년 %d월 %d일에 일정이 없습니다.\n아무키나 입력하세요.........",year,month,date);
	getchar();
	getchar();
	system("clear");
}


void show_calender(int scount,int storage[100][13][32],char schedule_storage[100][13][32][10]){		//일정이 있는 달을 찾아서 달력을 출력하게 해주는 함수
	int a=0,b=0,c=0;
	int year,month,date;

	while(scount>0){
		for(year=a;year<100;year++)
		{
			for(month=b;month<13;month++)
			{
				for(date=c;date<32;date++)
				{
					if(storage[year][month][date]==1)
					{
						a=year;
						b=month;
						c=date;

						calender(a,b,schedule_storage);
						a+=1;
						b+=1;
						c+=1;
						scount-=1;
					}
				}
			}
		}
	}
	printf("더이상의 스케줄이 없습니다.\n");
}

/*스케줄러의 메인함수*/

int scheduler(){																					//스케줄러의 메인함수
	int menu;
	int year,month,date;
	int storage[100][13][32] = {0};                                                                 //일정이 있을시 연,월,일에 대한 정보를 저장하기 위한 3차월배열
	int i;				
	int scount=0;       																			//일정의 개수를 카운트             
	int o=0;

	char schedule[10];																				
	char schedule_storage[100][13][32][10]={0};  													//일정이 있을시 연,월,일에 맞게 일정을 받아넣는 4차원 배열

	while(1){
		printf("메뉴\n1.스케줄 입력\n2.스케줄 삭제\n3.스케줄 보기\n4.Main menu\n");
		printf("메뉴 : ");
		scanf("%d",&menu);
		switch(menu){
			case 1:
				printf("입력 : ");
				scanf("%d%d%d%s",&year,&month,&date,schedule);
				if(year<2000 || year>2100){
					printf("해당 년도는 인식할 수 없습니다.\n\n");
					break;
				}
				year=year-2000;                                                                         

				if(storage[year][month][date] == 0)
				{

					storage[year][month][date] = 1;                                                     
					scount=scount+1;                                                                    
					s_input(year,month,date,schedule);

					for(i=0;i<10;i++)
					{
						schedule_storage[year][month][date][i]=schedule[i];                             
					}
				}
				else
				{
					o=over(year,month,date,schedule);
					if(o==1)
					{
						for(i=0;i<10;i++)
						{
							schedule_storage[year][month][date][i]=schedule[i];                             
						}
					}
				}

				break;



			case 2:

				printf("입력 : ");
				scanf("%d%d%d",&year,&month,&date);

				if(year<2000 || year>2100){
					printf("해당 년도는 스케줄 삭제가 불가능합니다.");
					break;
				}
				year=year-2000;


				if(storage[year][month][date] == 0)
				{
					delete_0(year,month,date);
				}
				else
				{
					for(i=0;i<10;i++)
					{
						schedule_storage[year][month][date][i]=0;
					}
					scount=scount-1;
					storage[year][month][date] = 0;
					delete_1(year,month,date);
				}
				break;



			case 3:
				show_calender(scount,storage,schedule_storage);

				break;


			case 4:
				system("clear");
				main();
				break;



			default:
				system("clear");
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


char input[2016]={'\0'},temp[2000]={'\0'};
double alpabat[26]={'\0'};
char spare[2016]={'\0'};

int top;
char math;

void temp_spare();
void cal();
void mv(int i);
void remove_math();
void remove_space();
void calculate();
void Transformation();
void Postfix_notation();
void Enter();
void move();
double search_math();
double in_to_al(int i);
double square(int i);

void peek();


int stack[MAX];
int top;


/* 스택 상단의 값 지정*/

void init_stack(){
	top = -1;
}

int push(int t){

	if (top >= MAX - 1){
		return -1;
	}

	stack[++top] = t;
	return t;
}

int pop(){
	if (top < 0){
		return -1;
	}
	return stack[top--];
}

void print_stack(){
	int i;
	for (i = top; i >= 0; i--){
		printf("%-6d", stack[i]);
	}
}

/*스택의 맨 윗값*/

int get_stack_top(void){
	return (top < 0) ? -1 : stack[top];
}


int is_stack_empty(){
	return (top < 0);
}


/*들어온 값이 연산자 인지 확인*/

int is_operator(int k){
	return (k == '+' || k == '-' || k == '*' || k == '/');
}



int is_legal(char *s){
	int f = 0;
	while (*s){


		while (*s == ' '){
			s++;
		}

		if (is_operator(*s)){
			f--;
		}
		else{
			f++;
			while (*s != ' '){
				s++;
			}
		}
		if (f < 1) break;
		s++;
	}
	return (f == 1);
}

/*연산자 우선순위의 수치화*/

int precedence(int op){
	if (op == '(') return 0;
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	else return 3;
}

/*입력된 식을 후위 연산식으로 바꿔주는 함수*/

void postfix(char *pff, char *strr){
	char c;
	init_stack();
	while (*strr){
		if (*strr == '('){
			push(*strr);
			strr++;
		}
		else if (*strr == ')'){
			while (get_stack_top() != '('){
				*pff++ = pop();
				*pff++ = ' ';
			}
			pop();

			strr++;
		}
		else if (is_operator(*strr)){
			while (!is_stack_empty() &&
					precedence(get_stack_top()) >= precedence(*strr)){
				*pff++ = pop();

				*pff++ = ' ';
			}
			push(*strr);
			strr++;
		}
		else if (*strr >= '0' && *strr <= '9'){
			do{
				*pff++ = *strr++;
			} while (*strr >= '0' && *strr <= '9');
			*pff++ = ' ';
		}
		else{
			strr++;
		}
	}

	while (!is_stack_empty()){
		*pff++ = pop();
		*pff++ = ' ';
	}
	pff--;
	*pff = 0;
}

/* 후위 연산식의 계산*/

int calc(char *p){
	int i;
	init_stack();
	while (*p){
		if (*p >= '0' && *p <= '9'){
			i = 0;
			do{
				i = i * 10 + *p - '0';
				p++;
			} while (*p >= '0' && *p <= '9');
			push(i);
		}
		else if (*p == '+'){
			push(pop() + pop());
			p++;
		}
		else if (*p == '*'){
			push(pop() * pop());
			p++;
		}
		else if (*p == '-'){
			i = pop();
			push(pop() - i);
			p++;
		}
		else if (*p == '/'){
			i = pop();
			push(pop() / i);
			p++;
		}
		else{
			p++;
		}
	}
	return pop();
}

/*딜레이*/

void delay(clock_t n)
{
	  clock_t start = clock();
	    while(clock() - start < n);
}


int remove_zero()
{
	int i=0, j,count =0, right;

	while(temp[i]!='.')
	{
		i=i+1;
	}
	right = i+6;
	j=right;

	while(right>i)
	{
		if(temp[right]> '0' && temp[right]<='9')
			break;
		else
		{
			temp[right]= '\0';
			right -=1;
		}
	}

	if(i==right)
	{
		temp[i] = '\0';
		right-=1;
	}
	if(math == 'r')
		right +=4;
	else if(math == '0')
		;
	else
		right +=3;

	return right +1;

}






void remove_space()
{
	int i=0, count =0;;

	while(input[i]!='\0')
	{
		if(input[i]==' ')
		{
			count = i;
			while(count != 2000)
			{
				input[count]=input[count+1];
				input[count +1] = '\0';
				count = count +1;
			}
		}
		else
			i=i+1;
	}

}


void cal()
{
	int i = 0 , count = 0, k = 1, alpa = 0, j = 1, spare = 0;

	char str[2016];
	char str_storage[100];
	double v_charicter[26];
	char pf[100];

	char num_str[100];
	char pm_str[100];

	int a=0,b=0;
	int c=0,d=0;
	int e,f;
	int g=0;
	char h;
	int r;

	double pf_no[100];

	input[0] = getchar();

	while(1)
	{
		printf("input: ");
		fgets(input,sizeof(input),stdin);
		memset(temp, '\0', sizeof(temp));
		remove_space();
		
		for(f=0;f<2016;f++){
		      str[f]=input[f];
		}


		in_to_al(search_math());
		if(strchr(input,'=') != NULL)
		{
			input[0] = atoi(input);
		}
		else if(input[0]=='!' && input[1]=='@' && input[2]=='#' && input[3]=='$')  
		{
			break;
		}
		else if(input[1] == '+' || input[1] == '-' || input[1] == '*' || input[1] == '/') 
		{
			calculate();
			k=1;
			while(input[k-1] !='\0')
			{
				input[k-1]='\0';
				k+=1;
			}
		}

		while(str[a] != '\0'){
			if(str[a]==' '){
				b=a;
				while(b != 100){
					str[b]=str[b+1];
					str[b+1]='\0';
					b=b+1;
				}
			}
			else
				a=a+1;
		}

		postfix(pf,str);
		delay(1500);
		printf("Postfix notation : %s\n",pf);
		delay(1500);
		printf("결과 : %d\n",calc(pf));
		delay(1000);
		printf("\n계속하려면 엔터키를 입력하시오.\n");
	getchar();
	getchar();
	system("clear");


	}


}

double search_math()
{
	int i;
	while(input[i]!='\0')
	{
		if(input[i]=='r')
		{
			math = 'r';
			return i+4;
		}
		else if(input[i]=='s')
		{
			math = 's';
			return i+3;
		}
		else if(input[i]=='c')
		{
			math = 'c';
			return i+3;
		}
		else if(input[i]=='t')
		{
			math = 't';
			return i+3;
		}
		else if(input[i]=='l')
		{
			math = 'l';
			return i+3;
		}
		else if(input[i]=='^')
		{
			math = '^';
			return i;
		}
		//		else
		//			return;
		i+=1;
	}
	//	if(input[i]=='\0')
	//		return;
}


double in_to_al(int i)
{
	if(math=='0')
	{
		mv(i);                                 
		return atof(temp);  
	}
	else if(math == 'r')
	{
		mv(i);
		return sqrt(atof(temp));
	}
	else if(math == 'l')
	{
		mv(i);
		return  log10(atof(temp));
	}
	else if(math =='s')
	{
		mv(i);
		return  sin(atof(temp));
	}
	else if(math =='c')
	{
		mv(i);
		return  cos(atof(temp));
	}
	else if(math =='t')
	{
		mv(i);
		return  tan(atof(temp));
	}
	else if(math == '^')
	{
		return square(i);
	}
}

double square(int i)
{
	double light,right;
	int k=1,j;
	j=i;
	j++;
	i--;
	while(input[i]>='0' && input[i] <='9')
		i-=1;
	i+=1;
	while(input[j]>='0' && input[j] <='9')
		j+=1;
	j-=1;
	mv(i);
	light = atof(temp);
	while(temp[k-1] !='\0')
	{
		temp[k-1]='\0';
		k+=1;
	}
	mv(j);
	right = atof(temp);
	return pow(light, right);
}


void mv(int i)
{
	int j;
	j=i;
	while((input[i]>='0' && input[i]<='9') || input[i] =='.')
	{
		temp[i-j]=input[i];
		i+=1;
	}
}


void calculate()
{

	Transformation();
	//	Postfix_notation();
}

void Transformation()
{
	int count, i=0, j,k=1, time=0;
	double aaa;

	while(input[i]!='\0')
	{
		aaa=0;
		k=1;
		while(temp[k-1] !='\0')
		{
			temp[k-1]='\0';
			k+=1;
		}
		if(input[i]>='A' && input[i]<='Z')
		{
			sprintf(temp,"%lf",alpabat[input[i] -65]);
			count =remove_zero();
			move(count,i);
			i+=1;
		}
		else if (input[i]=='r' || input[i]=='s' || input[i] == '^' || input[i] == 'c' || input[i] == 't' || input[i] == 'l')
		{
			k=i;
			j= search_math(i);
			if(input[j]>='A' && input[j]<='Z')
			{

				math='0';
				sprintf(temp,"%lf",alpabat[input[j] -65]);
				count =remove_zero();
				move(count,j);
				if(input[i]!='^')
					i=0;
			}
			else
			{
				aaa= in_to_al(j);
				printf("aaa:  %lf\n\n",aaa);
				sprintf(temp, "%lf",aaa);
				count =remove_zero();
				move(count,i);
				i+=1;
			}



		}
		else if(input[i] == '-' || input[i] == '+' || input[i] == '*' || input[i] == '/');
		i+=1;
	}
}


void Enter()
{
	printf("엔터눌러 \n");
	while(getchar() != '\n')
		;
}


void move(int right, int alpa_location)
{
	int l,i = 0, j = strlen(input)-1,a,n, k;
	k=alpa_location;
	a=j;
	while(j>alpa_location)
	{
		spare[j-k-1+i] = input[j];
		input[j]='\0';
		j-=1;
		i-=1;
	}
	i=0;
	while(alpa_location + right -1 >=j)
	{
		input[j]= temp[i];
		i+=1;
		j+=1;
	}
	printf("%s\n%s",spare,input);
	if(math == '^')
	{
		l=k;
		while(input[k-1]>='0' && input[k-1] <='9')
		{
			while(input[l]!='\0')
			{
				input[l-1]=input[l];
				l+=1;
			}
			k-=1;
		}
	}
}
int main(){

	int n;
	while(1)
	{
		printf("1.공학용 계산기\n2.스케줄 관리\n3.프로그램 종료\n");
		printf("선택 : ");
		scanf("%d",&n);

		switch(n){
			case 1:
				cal();
				break;
			case 2:
				scheduler();
				break;
			case 3:
				exit(-1);

		}
	}
}

