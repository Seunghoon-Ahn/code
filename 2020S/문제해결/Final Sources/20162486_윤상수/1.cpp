#include<stdio.h>
#include<stdlib.h>

int cnt;

int data[2200][2200];
int answer[3];
void Func(int x, int y, int size);
int main()
{
	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < cnt; j++)
			scanf("%d", &data[i][j]);
	}
	getchar();
	for (int i = 0; i < 3; i++)
		answer[i] = 0;

	Func(0, 0, cnt);
	for (int i = 0; i < 3; i++)
		printf("%d\n", answer[i]);
	return 0;
}
void Func(int x, int y, int size)
{
	int unity_trigger = 1;
	for (int i = x; i < (x + size); i++)
	{
		for (int j = y; j < (y + size); j++)
		{
			if (data[x][y] != data[i][j])
			{
				unity_trigger = 0;
				break;
			}
		}
	}
	if (unity_trigger == 1)
	{
		answer[data[x][y] + 1]++;
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			Func(x + (size / 3)*j, y + (size / 3)*i, size / 3);
	}
}