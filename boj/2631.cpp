#include <bits/stdc++.h>
using namespace std;
int n;
int arr[202];
int dp[202];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int res = 0;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	
	for(int i = 0; i < n; i++) {
		dp[i] = 1;
		for(int j = 0; j < i; j++) {
			if(arr[j] < arr[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		res = max(res, dp[i]);
	}
	cout << n - res;
	return 0;
}
