#include <bits/stdc++.h>
using namespace std;
int cable[502];
int N;
int dp[502];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int a, b, res = -1;
	cin >> N;
	for(int i = 1; i <= N; i++) {
		cin >> a >> b;
		cable[a] = b;
	}

	for(int i = 1; i <= 500; i++) {
		if(cable[i] == 0)
			continue;
		dp[i] = 1;
		for(int j = 1; j < i; j++) {
			if(cable[j] < cable[i])
				dp[i] = max(dp[i], dp[j] + 1);
		}
		res = max(res, dp[i]);
	}

	cout << N - res;
	return 0;
}
