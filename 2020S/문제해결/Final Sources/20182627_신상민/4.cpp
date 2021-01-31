#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int n, m, k;
vector<pair<int, int>> w[301];
int maximum;

void dfs(int now, int score, int cnt) {
	if (now == n) {
		maximum = max(score, maximum);
		return;
	}

	if (cnt >= m) return;

	for (int i = 0; i < w[now].size(); i++) {
		if (w[now][i].first > now) {
			dfs(w[now][i].first, score + w[now][i].second, cnt + 1);
		}
	}
}

int main() {
	cin >> n >> m >> k;

	for (int i = 1; i <= k; i++) {
		int s, e, c;
		cin >> s >> e >> c;
		w[s].push_back(make_pair(e, c));
	}
	dfs(1, 0, 1);
	cout << maximum << '\n';
	return 0;
}