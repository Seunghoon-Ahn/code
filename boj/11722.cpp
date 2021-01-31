#include <bits/stdc++.h>
using namespace std;
int N;
vector <int> v;
int dp[1001];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp, res = 0;
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	
	for(int i = 0; i < N; i++) {
		dp[i] = 1;

		for(int j = 0; j < i; j++) {
			if(v[j] > v[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		res = max(res, dp[i]);
	}

	cout << res << '\n';
	return 0;
}


