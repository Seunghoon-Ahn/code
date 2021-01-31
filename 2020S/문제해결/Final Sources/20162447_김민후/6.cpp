#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int n, m, day = 0, map[111][111], ccnt = 0;
int mv[][4] = { { 0,0,-1,1 },{ 1,-1,0,0 } };
void gogo(int a, int b)
{
	queue<pair<int, int>> go;
	int visit[111][111] = { 0 }, damage[111][111] = { 0 };
	go.push({ a,b });
	while (!go.empty())
	{
		int cura, curb;
		cura = go.front().first;	curb = go.front().second;
		//printf("%d %d\n", cura, curb);
		go.pop();
		if (visit[cura][curb]) continue;
		if (map[cura][curb])
		{
			if (damage[cura][curb]++)
			{
				damage[cura][curb] = 0;
				ccnt--;
				map[cura][curb] = 0;
				visit[cura][curb] = 1;
			}
		}
		else
		{
			visit[cura][curb] = 1;
			for (int i = 0; i < 4; i++)
			{
				if(!visit[cura+mv[0][i]][curb+mv[1][i]]&& cura+mv[0][i]>=0 && cura+mv[0][i]<=n && curb + mv[1][i] >= 0 && curb + mv[1][i] <= m)
					go.push({ cura + mv[0][i], curb + mv[1][i] });
			}
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j]) ccnt++;
		}
	}

	while (ccnt)
	{
		day++;
		gogo(0, 0);
		//for (int i = 1; i <= n; i++)
		//{
		//	for (int j = 1; j <= m; j++)
		//		printf("%d ", map[i][j]);
		//	printf("\n");
		//}
		//printf("\n");
	}
	printf("%d\n", day);
}

/*
8 9
0 0 0 0 0 0 0 0 0
0 0 0 1 1 0 0 0 0
0 0 0 1 1 0 1 1 0
0 0 1 1 1 1 1 1 0
0 0 1 1 1 1 1 0 0
0 0 1 1 0 1 1 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0

8 9
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0

9 9
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
*/