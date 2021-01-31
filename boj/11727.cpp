#include <bits/stdc++.h>
using namespace std;

long long dp[1002];
int main(void) {
	int n;
	cin >> n;
	dp[1] = 1;
	dp[2] = 3;

	for(int i = 3; i <= n; i++)
		dp[i] = (dp[i-2] * 2  + dp[i-1]) % 10007; 

	cout << (dp[n] % 10007);
	return 0;
}
