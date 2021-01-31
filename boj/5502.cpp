#include <bits/stdc++.h>
using namespace std;
string s1, s2;
int len;
int dp[5002][5002];
int main(void) {
	cin >> len;
	cin >> s1;
	s2 = s1;
	reverse(s2.begin(), s2.end());

	for(int i = 1; i <= len; i++) {
		for(int j = 1; j <= len; j++) {
			if(s1[i] == s2[j])
				dp[i][j] = dp[i-1][j-1] + 1;
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	cout << len - dp[len][len];
	return 0;
}

