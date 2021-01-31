#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int n, m, a, b;

int minCost = 2000000000;
int visit[1001];
vector<pair<int, int>> map[1001];

void dfs(int now, int cost) {
	if (now == b) {
		minCost = min(minCost, cost);
		return;
	}
	for (int i = 0; i < map[now].size(); i++) {
		int next = map[now][i].first;
		if (visit[next] == 0) {
			visit[next] = 1;
			dfs(next, cost + map[now][i].second);
			visit[next] = 0;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int s, e, w;
		cin >> s >> e >> w;
		map[s].push_back(make_pair(e, w));
	}
	cin >> a >> b;
	visit[1] = 1;
	dfs(1, 0);

	cout << minCost << '\n';
	return 0;
}