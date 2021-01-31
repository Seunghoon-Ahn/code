#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define leapyear(year) ((year)%4==0 && ((year)%100!=0 || (year)%400==0))                                        //윤년 판정식




/*
 * 후에 있는 show_calender 로부터 스케줄이 있는 년,월을 입력받아 그에 해당하는 달력을 출력하는 함수
 */

void calender(int year, int month, char schedule_storage[100][13][32][10]){										
	int e_date[]={0,31,28,31,30,31,30,31,31,30,31,30,31};									//1~12월까지의 마지막 날짜
	int l_year,day;																			
	int i,j,k;

	//*윤년 판정(윤년 시 2월은 29일)*//	
	if(month == 2 && leapyear(year))
	{
		e_date[2]=29;
	}
	
	//작년과 비교한 올해의 시작날짜//
	l_year=year-1;
	
	//달이 시작하는 위치를 계산하는 식//
	day = (l_year+(l_year/4)-(l_year/100)+(l_year/400)+1)%7;
	
	for(i=1;i < month;i++)
	{
		day += e_date[i];
	}
	day%=7;
	
	//달력 인터페이스//
	printf("\n                           %d년  %d월",year+2000,month);
	printf("\n       Sun.     Mon.    Tues.     Wed.    Thrus.    Fri.    Sat.\n");
	

	if(leapyear(year) && month>2)															//윤년일 시 3월부터 날짜를 1칸씩 뒤로 밈
	{
		for(i=-day;i<e_date[month]+1;i++)
		{
			if((i+day)%7==0)																//1주일 단위로 개행
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
						if(schedule_storage[year][month][j]==0)								//만약 일정이 있을 시 중간에 일정을 출력
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
	
	else																					//윤년이 아닐시....나머지는 위와 같은 식
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
	system("clear");																		//달력을 출력하고 엔터 입력시 다음 단계 실핻
	
}


//스케줄 입력시 정보를 출력하는 함수//

void input(int year,int month,int date,char schedule[]){
	
	printf("출력 : %d년 %d월 %d일 %s",year+2000,month,date,schedule);
	printf("\n일정을 추가하였습니다.\n아무키나 입력하세요..........");
	getchar();
	getchar();
	system("clear");
}

//스케줄 중복시 정보를 출력하는 함수//

void over(int year, int month, int date, char schedule[]){
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

//삭제 입력시 일정이 있을때 정보를 출력하는 함수//

void delete_1(int year, int month, int date){
		year+=2000;
		printf("%d년 %d월 %d일에 일정이 있습니다.\n일정을 삭제하였습니다.\n아무키나 입력하세요.........",year,month,date);
		getchar();
		getchar();
		system("clear");
}

//삭제 입력시 일정이 없을때 정보를 출력하는 함수//

void delete_0(int year, int month, int date){		
		year+=2000;
		printf("%d년 %d월 %d일에 일정이 없습니다.\n아무키나 입력하세요.........",year,month,date);
		getchar();
		getchar();
		system("clear");
	}

//스케줄이 있는 달력을 출력하게 만드는 함수//

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
	}//while ending
	printf("더이상의 스케줄이 없습니다.\n");
}

		
		

int main(){
	int menu;
	int year,month,date;
	int storage[100][13][32] = {0};																			//해당 년,월,일에 일정이 있는지 없는지 판별하기 위한 배열
	int i;
	int scount=0;																							//스케줄 개수를 담는 변수

		
	char schedule[10];																						
	char schedule_storage[100][13][32][10]={0};																//년,월,일에 일정을 집어넣는 변수
	

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
					year=year-2000;																			//이 스케줄러는 2000~2100년까지밖에 스케줄 입력을 받지 않는다

					if(storage[year][month][date] == 0)
					{
	
						storage[year][month][date] = 1;														//스케줄이 들어오면 해당 년,월,일에 해당하는 
						scount=scount+1;																	//스케줄의 개수를 추가
						input(year,month,date,schedule);													
					
						for(i=0;i<10;i++)
						{
							schedule_storage[year][month][date][i]=schedule[i];								//스케줄을 해당하는 연,월,일에 대입
						}
					}
					else
					{
						over(year,month,date,schedule);
					
						for(i=0;i<10;i++)
						{
							schedule_storage[year][month][date][i]=schedule[i];								//데이터를 덮어씀
						}

					}
	
					break;
	
	
	
			case 2: 
																											//데이터 삭제의 메커니즘은 input과 동일
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
					 break;
		
		
		
			default:
					 system("clear");
					 break;
		}	
	}	
}
