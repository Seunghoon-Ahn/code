#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<int, int>> edges[1001];
int n, m;
long long dist[1001];
int visit[1001] = { 0 };
int min(int a, int b)
{
	return a < b ? a : b;
}
void gogo(int s)
{
	visit[s] = 1;
	//printf("%d(%d):\n", s,dist[s]);
	for (auto &k : edges[s])
	{
		int togo = k.first, cost = k.second;
		if (dist[togo] <= dist[s] + cost) continue;
		//printf("%d -> %d : %d\n", s, togo,cost);
		dist[togo] = dist[s] + cost;
		gogo(togo);
	}
}
int main()
{
	int a, b, c;
	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		edges[a].push_back({ b,c });
	}
	scanf("%d%d", &a, &b);
	for (int i = 0; i <= n;i++) dist[i]= LLONG_MAX / 2;
	dist[a] = 0;
	gogo(a);
	printf("%lld\n", dist[b]);
}
/*
5
8
1 2 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1
3 5 1
4 5 3
1 5


2
1
1 2 0
1 2

5
9
1 2 4
1 3 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1
3 5 1
4 5 3
1 5
*/