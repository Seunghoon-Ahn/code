#include <bits/stdc++.h>
using namespace std;
long long dp[12][12];

long long combi(int n, int r) {
	if(dp[n][r] > 0)
		return dp[n][r];
	if(r == 0 || n == r)
		return dp[n][r] = 1;

	return dp[n][r] = combi(n-1, r-1) + combi(n-1, r);
}

int main(void) {
	int n, r;
	cin >> n >> r;
	cout << combi(n, r);
	return 0;
}

