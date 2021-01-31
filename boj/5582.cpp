#include <bits/stdc++.h>
using namespace std;
string s1, s2;
int dp[4002][4002];
int main(void) {
	int mmax = 0;
	cin >> s1 >> s2;
	s1 = ' ' + s1;
	s2 = ' ' + s2;

	for(int i = 1; i < s1.size(); i++) {
		for(int j = 1; j < s2.size(); j++) {
			if(s1[i] == s2[j])
				dp[i][j] = dp[i-1][j-1] + 1;
			if(dp[i][j] > mmax)
				mmax = dp[i][j];
		}
	}
	cout << mmax;
	return 0;
}



