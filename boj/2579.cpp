#include <bits/stdc++.h>
using namespace std;
int s[302];
int dp[302];
int main(void) {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> s[i];
	dp[1] = s[1];
	dp[2] = s[2] + s[1];
	dp[3] = max(dp[1] + s[3], s[2] + s[3]);
	for(int i = 4; i <= n; i++) {
		dp[i] = max(dp[i-2] + s[i], dp[i-3] + s[i-1]+s[i]);
	}
	cout << dp[n];
	return 0;
}
	
