#include <bits/stdc++.h>
using namespace std;
int n, k;
int c[103];
int dp[10003];
int main(void) {
	cin >> n >> k;
	for(int i = 0; i < n; i++)
		cin >> c[i];
	dp[0] = 1;
	for(int x = 0; x < n; x++)
		for(int y = c[x]; y <= k; y++)
			dp[y] += dp[y - c[x]];
	cout << dp[k];
	return 0;
}

