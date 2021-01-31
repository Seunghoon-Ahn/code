#include <bits/stdc++.h>
using namespace std;
int N, Q;
int f[200002];
int dp[20][200002];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int tmp;
	for(int i = 1; i <= N; i++) {
		cin >> f[i];
		dp[0][i] = f[i];
	}
	for(int i = 1; i < 20; i++)
		for(int j = 1; j <= N; j++)
			dp[i][j] = dp[i-1][dp[i-1][j]];

	
	int Q;
	cin >> Q;
	int n, x;
	for(int i = 0; i < Q; i++) {
		cin >> n >> x;
		for(int i = 0; i < 20; i++)
			if(n & (1 << i))
				x = dp[i][x];
		

		cout << x << '\n';
	}
	return 0;
}

