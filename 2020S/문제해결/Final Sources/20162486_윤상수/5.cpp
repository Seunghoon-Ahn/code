#include<stdio.h>
#include<stdlib.h>

int S[22][22];
int N;

void tree(int now,int point,int cnt);

bool queue[22];
int answer=10000;
int check(int a,int b);
int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			scanf("%d", &S[i][j]);
		getchar();
		queue[i] = false;
	}
	queue[1] = true;
	tree(1,0,(N/2));
	printf("%d\n", answer);
	return 0;
}
void tree(int now,int point,int cnt)
{
	if(cnt==1)
	{
		int tmp = 0, rest = 0;
		for (int j = 1; j <= N; j++)
		{
			for (int k = 1; k <= N; k++)
			{
				if (queue[j] && queue[k])
				{
					tmp += S[j][k];
				}
				else if (!queue[j] && !queue[k])
					rest += S[j][k];
			}
		}
		tmp = check(rest, tmp);
		if (answer > tmp)
			answer = tmp;
		return;
	}
	for (int i=now+1; i <= N; i++)
	{
		if(cnt>1)
		{
			queue[i] = true;
			tree(i, point + S[now][i] + S[i][now], cnt - 1);
			queue[i] = false;
		}
	}
}
int check(int a, int b)
{
	int c = a - b;
	if (c> 0)
		return c;
	else
		return -c;
}