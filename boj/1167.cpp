#include <bits/stdc++.h>
using namespace std;
int V;
vector<pair<int, int>> t[100003];
int len[100003];

void dfs(int n, int prev) {
	for(auto tmp : t[n]) {
		int next = tmp.first;
		int cost = tmp.second;
		if(next == prev)
			continue;
		len[next] = len[n] + cost;
		dfs(next, n);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> V;
	for(int i = 1; i <= V; i++) {
		int dot;
		cin >> dot;
		while(1) {
			int tmp1, tmp2;
			cin >> tmp1;
			if(tmp1 == -1)
				break;
			cin >> tmp2;
			t[dot].push_back({tmp1, tmp2});
		}
	}
	dfs(1, 0);
	int mx = 1;
	for(int i = 1; i <= V; i++)
		if(len[mx] < len[i])
			mx = i;
	memset(len, 0, sizeof(len));
	dfs(mx, 0);
	int my = 1;
	for(int i = 1; i <= V; i++)
		if(len[my] < len[i])
			my = i;
	cout << len[my] << '\n';
	return 0;
}

