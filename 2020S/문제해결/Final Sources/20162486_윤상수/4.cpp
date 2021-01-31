#include<stdio.h>
#include<stdlib.h>

int N, M, K;

int data[310][310];

int dp[310][310];

int answer = 0;
void Func(int start, int cnt);
int main()
{
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			data[i][j] = 0;
			dp[i][j] = 0;
		}
	}
	int x, y,p;
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d %d", &x, &y, &p);
		if (data[x][y] < p)
			data[x][y] = p;
	}
	dp[1][1] = 0;
	Func(1,M-1);
	printf("%d\n", dp[1][N]);
}
void Func(int start,int cnt)
{
	if (start >= N)
		return;
	for (int i = start+1; i <= N; i++)
	{
		if(data[start][i]!=0)
		{
			if (dp[1][start] + data[start][i] > answer)
			{
				answer = dp[1][start] + data[start][i];
				dp[1][i] = answer;
			}
		}
	}
	if(cnt>1)
	{
		for (int i = start + 1; i < N; i++)
		{
			if (data[start][i] != 0)
				Func(i, cnt - 1);
		}
	}
}