#include <bits/stdc++.h>
using namespace std;
int arr[101010];
int dp[101010];
int main(void) {
	int i, n;
	int res = 0;

	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	dp[0] = arr[0];
	res = dp[0];
	for(int i = 1; i < n; i++) {
		dp[i] = max(dp[i-1] + arr[i], arr[i]);
		res = max(res, dp[i]);
	}
	cout << res << '\n';
	return 0;
}

