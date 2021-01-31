#include <bits/stdc++.h>
using namespace std;
vector <pair<int, int>> g[40003];
int N;
pair<int,int> dp[20][40003];
int h[40003];
int val[40003];

void dfs(int n, int prev) {
	for(auto next : g[n]) {
		if(next.first == prev)
			continue;
		h[next.first] = h[n] + 1;
		dp[0][next.first].first = n;
		val[next.first] = val[n] + next.second;
		dfs(next.first, n);
	}
}

int LCA(int a, int b) {
	if(h[a] < h[b])
		swap(a, b);
	int gap = h[a] - h[b];
	for(int i = 0; i < 20; i++) {
		if(gap & (1 << i)) {
			a = dp[i][a].first;
		}
	}
	if(a == b)
		return a;
	for(int i = 19; i >= 0; i--) {
		if(dp[i][a].first != dp[i][b].first) {
			a = dp[i][a].first;
			b = dp[i][b].first;
		}
	}
	
	return dp[0][a].first;
}

int calcul(int a, int b, int par) {
	return val[a] + val[b] - (val[par] * 2);
}


int main(void) {
	cin >> N;
	int tmp1, tmp2, tmp3;
	for(int i = 0; i < N-1; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		g[tmp1].push_back({tmp2, tmp3});
		g[tmp2].push_back({tmp1, tmp3});
	}
	dfs(1, 0);
	for(int i = 1; i < 20; i++)
		for(int j = 1; j <= N; j++) {
			dp[i][j].first = dp[i-1][dp[i-1][j].first].first;
			dp[i][j].second = dp[i-1][dp[i-1][j].first].second + dp[i-1][j].second;
		}
	
	int Q;
	cin >> Q;
	while(Q--) {
		cin >> tmp1 >> tmp2;
		int samepar = LCA(tmp1, tmp2);
		cout << calcul(tmp1, tmp2, samepar) << '\n';
	}
	return 0;
}

