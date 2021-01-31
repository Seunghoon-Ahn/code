#include<stdio.h>
#include<vector>
#include<utility>

using namespace std;
int map[101][101];
//0 빈공간
//1 치즈
//2 공기
int N, M;

void air(int x, int y)
{
	if (x < 0 || y<0 || x> M || y>N)
	{
		return;
	}

	if (map[y][x + 1] == 0)
	{
		map[y][x + 1] = 2;
		air(x + 1, y);
	}
	if (map[y + 1][x] == 0)
	{
		map[y + 1][x] = 2;
		air(x, y + 1);
	}
	if (map[y][x - 1] == 0)
	{
		map[y][x - 1] = 2;
		air(x - 1, y);
	}
	if (map[y - 1][x] == 0)
	{
		map[y - 1][x] = 2;
		air(x, y - 1);
	}
	return;
}

int scan()
{
	vector<pair<int, int>> v;
	int ret=0;
	for (int i = 1; i < N-1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			int airc=0;
			if (map[i][j] == 1)
			{
				if (map[i][j + 1] == 2)
				{
					airc++;
				}
				if (map[i + 1][j] == 2)
				{
					airc++;
				}
				if (map[i][j - 1] == 2)
				{
					airc++;
				}
				if (map[i - 1][j] == 2)
				{
					airc++;
				}
				if (airc >= 2)
				{
					ret=1;
					v.push_back(make_pair(i, j));
				}
			}
		}
	}

	for (auto& a : v)
	{
		map[a.first][a.second] = 2;
		air(a.first, a.second);
	}
	return ret;
}

int main()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	map[0][0] = 2;
	air(0, 0);	
	int ans=0;

	while (true)
	{
		int t = scan();		
		if (t > 0)
		{
			ans += t;
		}
		else
		{
			printf("%d", ans);
			break;
		}
	}

	return 0;
}