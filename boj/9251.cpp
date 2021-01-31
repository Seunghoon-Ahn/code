#include <bits/stdc++.h>
using namespace std;
char arr1[1002];
char arr2[1002];
int dp[1002][1002];
int len1, len2;
int main(void) {
	cin >> arr1;
	cin >> arr2;
	len1 = strlen(arr1);
	len2 = strlen(arr2);

	for(int i = 1; i <= len1; i++) {
		for(int j = 1; j <= len2; j++) {
			if(arr1[i-1] == arr2[j-1])
				dp[i][j] = dp[i-1][j-1] + 1;
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	cout << dp[len1][len2];
	return 0;
}



