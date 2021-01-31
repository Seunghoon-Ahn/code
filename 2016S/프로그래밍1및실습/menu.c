#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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
int search_math(int i);
double in_to_al(int i);
double square(int i);

void pop();
void push();
void peek();

char input[2016]={'\0'},temp[2000]={'\0'};
double alpabat[26]={'\0'};
char spare[2016]={'\0'};

int top =-1;
char math;


/****************
 *				*
 *   메인 메뉴 *
 *				*
 ****************/
int main(void) 
{
	int n;
	do
	{
		printf("1.공학용 계산기\n2.스케줄 관리\n3.프로그램 종료\n");
		scanf("%d",&n);
	
		if(n!=1 && n!=2 && n!=3)
			continue;
	
		else if (n==1)
			cal();
	
		else if (n==2)
			cal();
	
		else
			break;

	}while(1); 
	
	system("clear");
	return 0;
}
/************************
 *						*
 *    입력, 저장 탈출	*
 *						*
 ************************/
void cal(void)
{
	int i = 0 , count = 0,k=1, alpa = 0, j = 1, spare =0;
	
	input[0] = getchar();

	while(1)
	{
		printf("input: ");
		fgets(input,sizeof(input),stdin);
	
		i = 0;	
		
		k=1;
		while(temp[k-1] !='\0')
		{
			temp[k-1]='\0';
			k+=1;
		}
		printf("초기화 후 temp  %s\n\n", temp);
		remove_space();
		if(input[1] == '=')
		{
			j = search_math(2);
		
	 		alpabat[input[0] - 65] = in_to_al(j);
			printf("입력 알파%lf\n\n\n", alpabat[input[0] - 65]);
		}

		else if(input[0]=='!' || input[0]=='@' || input[0]=='#' || input[0]=='$')  //  탈출
			break;
	
	
		else if(input[1] == '+' || input[1] == '-' || input[1] == '*' || input[1] == '/') // 계산 시작
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
			printf("정확히 입력하시오\n");  // 그 이외의 것은 다시 
			continue;
		}
	}

	system("clear");

}

int search_math(int i)
{
	int j;
	j=i;
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
		else
		{
			math = '0';
		}
		i+=1;
	}
	if(input[i]=='\0')
		return j;
}
double in_to_al(int i)
{
	if(math=='0')
	{
		mv(i); 								   // 
		return atof(temp);   //  입력받은 숫자를 정수형 알파뱃 배열에 입력하는 과정
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

/********************
 *					*
 *    스페이스 제거	*
 *					*
 *********************/
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
/************************************
 *  								*
 *  예비용배열에 문자형으로 숫자입력*
 *									*
 ************************************/
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
/********
 *		*
 *  뭐	*
 *		*
 ********/
void calculate()
{
	
	Transformation();
	Postfix_notation();
}
/********************
 *					*
 *   일반 연산 함수 *
 *					*
 ********************/
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
/********************************************
 *											*
 *   정수면 정수로 소수면 뒤에 0전부 삭제	*
 *											*
 ********************************************/
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
/*************************************
 *									*
 *   숫자 길이만큼 오른쪽으로 땡기기*
 * 									*
 *************************************/
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
	printf("sssss%s\niiiii%s",spare,input);
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
			l=k;
		}
	}
	i=0;
	while(spare[i]!='\0')
	{
		input[j]=spare[i];
		j++;
		i++;
	}
}

void Postfix_notation()
{
}
	






