#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define leapyear(year) ((year)%4==0 && ((year)%100!=0 || (year)%400==0))
#include <math.h>
int main();

char input[100]={'\0'},temp[100]={'\0'};
double alpabat[26]={'\0'};
char spare[100]={'\0'};

int top =-1;
char math;


void calender(int year, int month, char schedule_storage[100][13][32][10]){
	int e_date[]={0,31,28,31,30,31,30,31,31,30,31,30,31};                                   
	int l_year,day;
	int i,j,k;


	if(month == 2 && leapyear(year))
	{
		e_date[2]=29;
	}


	l_year=year-1;


	day = (l_year+(l_year/4)-(l_year/100)+(l_year/400)+1)%7;

	for(i=1;i < month;i++)
	{
		day += e_date[i];
	}
	day%=7;

	printf("\n                           %d년  %d월",year+2000,month);
	printf("\n       Sun.     Mon.    Tues.     Wed.    Thrus.    Fri.    Sat.\n");


	if(leapyear(year) && month>2)                                                           
	{
		for(i=-day;i<e_date[month]+1;i++)
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
					for(j=i-7;j<i;j++)
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
	else                                                                                    
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
	system("clear");                                                                       

}

void s_input(int year,int month,int date,char schedule[]){

	printf("출력 : %d년 %d월 %d일 %s",year+2000,month,date,schedule);
	printf("\n일정을 추가하였습니다.\n아무키나 입력하세요..........");
	getchar();
	getchar();
	system("clear");
}

int over(int year, int month, int date, char schedule[]){
	char yon;
	printf("출력 : %d년 %d월 %d일 %s",year+2000,month,date,schedule);
	printf("\n%d년 %d월 %d일에 일정이 있습니다.\n일정을 덮어쓰시려면 Y를, 취소하려면 N을 입력하세요 : ",year+2000,month,date);
	getchar();
	scanf("%c",&yon);
	if(yon== 'y')
	{
		printf("\n일정을 추가하였습니다.\n아무키나 입력하세요.........");
		getchar();
		getchar();
		system("clear");
		return 1;
	}
	else if(yon == 'n')
	{
		system("clear");
	}
	else
	{
		printf("잘못된 입력입니다\n아무키나 입력하세요.........");
		system("clear");
		getchar();
		getchar();
	}
}


void delete_1(int year, int month, int date){
	year+=2000;
	printf("%d년 %d월 %d일에 일정이 있습니다.\n일정을 삭제하였습니다.\n아무키나 입력하세요.........",year,month,date);
	getchar();
	getchar();
	system("clear");
}


void delete_0(int year, int month, int date){
	year+=2000;
	printf("%d년 %d월 %d일에 일정이 없습니다.\n아무키나 입력하세요.........",year,month,date);
	getchar();
	getchar();
	system("clear");
}


void show_calender(int scount,int storage[100][13][32],char schedule_storage[100][13][32][10]){
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


int scheduler(){
	int menu;
	int year,month,date;
	int storage[100][13][32] = {0};                                                                         
	int i;
	int scount=0;                                                                                           
	int o=0;

	char schedule[10];
	char schedule_storage[100][13][32][10]={0};                                                             

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

void pop();
void push();
void peek();

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

	printf("\n%s\n", input);
}
void cal(void)
{
	int i = 0 , count = 0, k = 1, alpa = 0, j = 1, spare = 0;

	input[0] = getchar();

	while(1)
	{
		printf("input: ");
		fgets(input,sizeof(input),stdin);
		printf("%s", input);

		memset(temp, '\0', sizeof(temp));

		printf("초기화 후 temp  %s\n\n", input);


		remove_space();

		in_to_al(search_math());

		if(strchr(input,'=') != NULL)
		{

			input[0] = atoi(input);
			printf("입력 알파%d\n\n\n", atoi(input));
		}

		else if(input[0]=='!' && input[1]=='@' && input[2]=='#' && input[3]=='$')  
			break;


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
		else
		{
			printf("정확히 입력하시오\n");  
			continue;
		}
	}

	system("clear");

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
	printf("mv후의 temp  %s\n", temp);
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
			printf("%s\n\n", input);
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

			printf("%s\n\n",input);


		}
		else if(input[i] == '-' || input[i] == '+' || input[i] == '*' || input[i] == '/');
		i+=1;
		printf("%d\n\n", i);
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

