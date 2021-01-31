#include <bits/stdc++.h>
using namespace std;
long long dp[92];
int main(void) {
	int n;
	cin >> n;
	int tmp1 = 0;
	int tmp2 = 1;
	dp[1] = 1;
	
	for(int i = 2; i <= n; i++) {
		long long ntmp1 = tmp1 + tmp2;
		long long ntmp2 = tmp1;

		dp[i] = ntmp1 + ntmp2;
		tmp1 = ntmp1;
		tmp2 = ntmp2;
	}
	cout << dp[n];
	return 0;
}
