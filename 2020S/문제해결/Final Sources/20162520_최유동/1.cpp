#include<stdio.h>
#define MaxN 2187

int N;
int mp = 0, zp = 0, pp = 0;

int map[MaxN][MaxN];

int scan(int sx, int sy, int size)
{
	int flag = map[sy][sx];
	for (int i = sy; i < sy + size; i++)
	{
		for(int j = sx; j < sx + size; j++)
		{
			if (flag != map[i][j]) return -2;
		}
	}
	return flag;	
}

void slice(int sx, int sy, int size)
{
	if (size == 1)
	{
		switch (map[sy][sx])
		{
		case 1:
			pp++;
			break;
		case 0:
			zp++;
			break;
		case -1:
			mp++;
			break;
		}
		return;
	}
	int res = scan(sx, sy, size);
	switch (res)
	{
	case -2://slice
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				slice(sx + (size / 3)*j, sy + (size / 3)*i, size / 3);
			}
		}
		break;
	case 1:
		pp++;
		break;
	case 0:
		zp++;
		break;
	case -1:
		mp++;
		break;
	}
}

int main()
{
	scanf("%d", &N);
	
	if (N > 1)
	{
		for (int i = 0; i <N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}
	}
	else
	{
		int tval;
		scanf("%d", &tval);
		switch (tval)
		{
		case -1:
			printf("1\n0\n0");
			return 0;
		case 0:
			printf("0\n1\n0");
			return 0;
		case 1:
			printf("0\n0\n1");
			return 0;
		default:
			return 0;
		}
	}

	slice(0,0,N);
	printf("%d\n%d\n%d",mp,zp,pp);

	return 0;
}