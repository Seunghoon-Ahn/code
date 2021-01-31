#include<stdio.h>
#include<stdlib.h>

int graph[110][110];
int chkg[110][110];

int N, M;

bool time_after();
void cheezing(int x, int y);
int answer = 0;
int main()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			scanf("%d", &graph[i][j]);
		getchar();
	}
	while (1)
	{
		answer++;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				chkg[i][j] = 0;
		}
		if (time_after())
			break;
	}
	printf("%d",answer);
	return 0;

}
bool time_after()
{
	for(int i=0;i<M;i++)
	{
		graph[0][i] = -1;
		cheezing(0, i);
		graph[N - 1][i] = -1;
		cheezing(N - 1, i);
	}
	for (int i = 0; i < N; i++)
	{
		graph[i][0] = -1;
		cheezing(i,0);
		graph[i][M-1] = -1;
		cheezing(i,N-1);
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (graph[i][j] == -1)
				graph[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (graph[i][j] == 1)
				return false;
		}
	}
	return true;
}
void cheezing(int x, int y)
{
	if (x >= 1)
	{
		if (graph[x - 1][y] == 0)
		{
			graph[x - 1][y] = -1;
			cheezing(x - 1, y);
		}
		else
		{
			chkg[x - 1][y]++;
			if(chkg[x-1][y]>=2)
				graph[x - 1][y] = -1;
		}
	}
	if (y >= 1)
	{
		if (graph[x][y-1] == 0)
		{
			graph[x][y - 1] = -1;
			cheezing(x, y-1);
		}
		else
		{
			chkg[x][y - 1]++;
			if (chkg[x][y - 1] >= 2)
				graph[x][y - 1] = -1;
		}
	}
	if (x + 1 < N)
	{
		if(graph[x+1][y]==0)
		{
			graph[x + 1][y] = -1;
			cheezing(x + 1, y);
		}
		else
		{
			chkg[x + 1][y]++;
			if (chkg[x + 1][y] >= 2)
				graph[x + 1][y] = -1;
		}
	}
	if (y + 1 < N)
	{
		if (graph[x][y + 1] == 0)
		{
			graph[x][y + 1] = -1;
			cheezing(x, y+1);
		}
		else
		{
			chkg[x][y + 1]++;
			if (chkg[x][y + 1] >= 2)
				graph[x][y + 1] = -1;
		}
	}
}