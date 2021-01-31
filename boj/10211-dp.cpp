#include <bits/stdc++.h>
using namespace std;
int dp[1010];
int T, N;
int arr[1010];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	while(T--) {
		memset(dp, 0, sizeof(dp));
		memset(arr, 0, sizeof(arr));
		int maxS = INT_MIN;
		cin >> N;
		for(int i = 0; i < N; i++)
			cin >> arr[i];
		dp[0] = arr[0];
		for(int i = 1; i < N; i++) {
			dp[i] = arr[i];
			if(arr[i] + dp[i-1] > dp[i])
				dp[i] = arr[i] + dp[i-1];
			maxS = max(maxS, dp[i]);
		}
		cout << maxS << '\n';
	}
	return 0;
}
