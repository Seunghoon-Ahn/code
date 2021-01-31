#include <bits/stdc++.h>
using namespace std;
vector <pair<int, int>> v;
int N, K;
int dp[102][100004];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp1, tmp2;
	cin >> N >> K;
	v.push_back({0,0});
	for(int i = 0; i < N; i++) {
		cin >> tmp1 >> tmp2;
		v.push_back({tmp1, tmp2});
	}

	for(int i = 1; i <= N; i++) {
		for(int j = 0; j <= K; j++) {
			if(v[i].first <= j)
				dp[i][j] = max(dp[i-1][j - v[i].first] + v[i].second, dp[i-1][j]);
			else
				dp[i][j] = dp[i-1][j];
		}
	}
	cout << dp[N][K];
	return 0;
}


