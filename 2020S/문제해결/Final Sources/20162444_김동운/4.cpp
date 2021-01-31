#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define P pair<int,int>

using namespace std;
const int MN = 301;

int N, M, K;
vector<P> g[MN];
bool visited[MN];
int dist[MN];
void dfs(int depth, int n, int cost) {
	if (depth > M) return ;

	int tmp = 0;
	for (P next : g[n]) {
		int w = next.first;
		int nxt = next.second;
		dist[nxt] = max(dist[nxt], cost + w);
		dfs(depth + 1, nxt, cost + w);
	}
}

int main(void)
{
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		int a, b, c;	cin >> a >> b >> c;
		if (a < b)
			g[a].push_back({ c,b });
	}
	
	dfs(0, 1, 0);
	cout << dist[N];
}