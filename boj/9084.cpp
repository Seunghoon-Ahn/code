#include <bits/stdc++.h>
using namespace std;
vector <int> res;
int T, N, M;
int c[22];
int dp[10003];
int main(void) {
	cin >> T;
	for(int i = 0; i < T; i++) {
		//memset(dp, 0, sizeof(dp));
		cin >> N;
		for(int j = 0; j < N; j++)
			cin >> c[j];
		cin >> M;
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for(int x = 0; x < N; x++)
			for(int y = c[x]; y <= M; y++)
				dp[y] += dp[y - c[x]];
		res.push_back(dp[M]);
	}
	for(int i = 0; i < T; i++)
		cout << res[i] << '\n';
	return 0;
}

