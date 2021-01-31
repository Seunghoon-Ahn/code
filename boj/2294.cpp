#include <bits/stdc++.h>
using namespace std;
int dp[10003];
int n, k;
int c[102];
int main(void) {
	cin >> n >> k;
	for(int i = 1; i <= k; i++)
		dp[i] = 10003;
	for(int i = 1; i <= n; i++) {
		cin >> c[i];

		for(int j = c[i]; j <= k; j++)
			dp[j] = min(dp[j], dp[j-c[i]] + 1);
	}
	
	if(dp[k] == 10003)
		cout << -1;
	else
		cout << dp[k] << '\n';

	return 0;
}

