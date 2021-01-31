#include <bits/stdc++.h>
using namespace std;
int arr[10004];
int dp[10004];

int main(void) {
	int n, mmax = -1;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> arr[i];
	dp[0] = 0;
	dp[1] = arr[1];
	dp[2] = arr[1] + arr[2];
	//dp[3] = max(dp[2], max(dp[1] + arr[3], arr[2] + arr[3]));

	for(int i = 3; i <= n; i++) {
		dp[i] = max(dp[i-1], max(dp[i-2] + arr[i], dp[i-3] + arr[i-1] + arr[i]));
		if(dp[i] > mmax)
			mmax = dp[i];
	}
	if(n == 2)
		mmax = arr[1] + arr[2];
	if(n == 1)
		mmax = arr[1];
	cout << mmax;
	return 0;
}
