#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MN = 202;
const int INF = 1e9;

vector<int> g[MN];
int c[MN][MN], f[MN][MN];
int MaxFlow(int src, int snk)
{
	int ret = 0;
	while (1) {
		queue<int> q; q.push(src);
		vector<int> p(MN, -1); p[src] = src;
		while (!q.empty()) {
			int n = q.front(); q.pop();
			for (int next : g[n]) {
				if (c[n][next] - f[n][next] > 0 && p[next] == -1) {
					q.push(next);
					p[next] = n;
				}
			}
		}
		if (p[snk] == -1) break;
		int flow = INF;
		for (int i = snk; i != src; i = p[i])
			flow = min(flow, c[p[i]][i] - f[p[i]][i]);
		for (int i = snk; i != src; i = p[i]) {
			f[p[i]][i] += flow;
			f[i][p[i]] -= flow;
		}
		ret += flow;
	}
	return ret;
}

int main(void)
{
	int N, M;	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;	cin >> a >> b;
		g[a].push_back(b + 100);
		g[b + 100].push_back(a);
		c[a][b + 100] = 1;
	}

	for (int i = 1; i <= N; i++) {
		g[0].push_back(i);
		g[i].push_back(i);
		c[0][i] = 1;

		g[201].push_back(i + 100);
		g[i + 100].push_back(201);
		c[i + 100][201] = 1;
	}

	cout << MaxFlow(0, 201);
}