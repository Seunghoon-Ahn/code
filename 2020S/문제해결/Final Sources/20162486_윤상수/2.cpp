#include<stdio.h>
#include<stdlib.h>

int N, M;

int Timek[100010];
int restTime[100010];

int answer = 0;

int main()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &Timek[i]);
		restTime[i] = 0;
	}
	int tmp;
	for (int i = 0; i < M; i++)
	{
		tmp = 0;
		for (int j = 0; j < N; j++)
		{
			if (restTime[tmp] + Timek[tmp] > restTime[j] + Timek[j])
				tmp = j;
		}
		restTime[tmp] += Timek[tmp];
	}

	tmp = 0;
	for (int i = 0; i < N; i++)
	{
		if (restTime[tmp] < restTime[i])
			tmp = i;
	}
	printf("%d\n", restTime[tmp]);
	return 0;
}