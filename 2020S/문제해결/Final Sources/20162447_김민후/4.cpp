#include <stdio.h>
#include <vector>
using namespace std;
vector<pair<int,int>> edges[301];
int n, m, k;
long long dp[303][303] = { 0 };
long long max(long long a, long long b)
{
	return a > b ? a : b;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int a, b, c;
	for (int i = 0; i < k; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		if (a > b) continue;
		edges[a].push_back({ b,c });
	}
	for (int i = 1; i <= m; i++)
	{
		for (int c = 1; c <= n; c++)
		{
			for (auto &k : edges[c])
				dp[k.first][i] = max(dp[c][i - 1] + k.second, dp[k.first][i]);
		}
	}
	printf("%lld\n", dp[n][m]);
}

/*
3 3 5
1 3 10
1 2 5
2 3 3
1 3 4
3 1 100

3 3 5
1 3 1
1 2 5
2 3 3
1 3 4
3 1 100

4 4 6
1 3 6
1 2 2
2 3 3
3 4 4
2 4 10
3 2 100
*/