#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int map[111][111],matched[111],visit[111] = { 0 };
int n, m,matches;
vector<int> claim[111];
int dfs(int t)
{
	visit[t] = 1;
	for (auto &k : claim[t])
	{
		if (!matched[k]) { matched[k] = t; return true; }
		if (!visit[matched[k]] && dfs(matched[k])) 
		{

			matched[k] = t;
			return true;
		}
	}
	return false;
}
void bimatch(int t)
{
	memset(visit, 0, sizeof(visit));
	if(dfs(t)) matches++;
}
int main()
{
	int a, b;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &a, &b);
		map[a][b] = 1;
		claim[a].push_back(b);
	}

	for (int i = 1; i <= n; i++)
	{
		bimatch(i);
	}
	printf("%d\n", matches);
}

/*
5 5
1 1
2 2
3 3
4 4
5 5

3 3
1 2
2 2
3 2

5 13
1 2
1 3
2 2
2 3
3 1
3 2
4 1
4 2
5 1
5 2
5 3
5 4
5 5

*/