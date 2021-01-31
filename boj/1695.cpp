#include <bits/stdc++.h>
using namespace std;
int len;
vector <int> v;
int dp[5002][5002];
int main(void) {
	int tmp;
	cin >> len;
	for(int i = 0; i < len; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}

	for(int i = 1; i <= len; i++) {
		for(int j = 1; j <= len; j++) {
			if(v[i - 1] == v[len - j])
				dp[i][j] = dp[i-1][j-1] + 1;
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	cout << len - dp[len][len];
	return 0;
}

