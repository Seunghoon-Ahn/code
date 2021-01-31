#include <bits/stdc++.h>
using namespace std;
long long dp[1004][1004];

long long combi(int n, int r) {
	if(dp[n][r] > 0)
		return dp[n][r];
	if(n == 0)
		return dp[n][r] = 0;
	if(r == 0 || n == r)
		return dp[n][r] = 1;
	

	return dp[n][r] = (combi(n-1, r-1) + combi(n-1, r)) % 10007;
}

int main(void) {
	int n, r;
	cin >> n >> r;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= i; j++)
			int tmp = combi(i, j);

	cout << dp[n][r];
	return 0;
}

