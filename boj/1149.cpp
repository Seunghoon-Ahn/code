#include <bits/stdc++.h>
using namespace std;
int h[1002][3];
int dp[1002][3];
int main(void) {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> h[i][0] >> h[i][1] >> h[i][2];
	dp[1][0] = h[1][0];
	dp[1][1] = h[1][1];
	dp[1][2] = h[1][2];

	for(int i = 2; i <= n; i++) {
		dp[i][0] = min(h[i][0] + dp[i-1][1], h[i][0] + dp[i-1][2]);
		dp[i][1] = min(h[i][1] + dp[i-1][0], h[i][1] + dp[i-1][2]);
		dp[i][2] = min(h[i][2] + dp[i-1][0], h[i][2] + dp[i-1][1]);
	}
	cout << min(dp[n][0], min(dp[n][1], dp[n][2]));
	return 0;
}
