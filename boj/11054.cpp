#include <bits/stdc++.h>
using namespace std;
int dp1[1002];
int dp2[1002];
int arr[1002];
int n;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;

	for(int i = 0; i < n; i++)
		cin >> arr[i];

	for(int i = 0; i < n; i++) {
		dp1[i] = 1;
		for(int j = 0; j < i; j++)
			if(arr[j] < arr[i])
				dp1[i] = max(dp1[i], dp1[j] + 1);
	}

	reverse(arr, arr + n);

	for(int i = 0; i < n; i++) {
		dp2[i] = 1;
		for(int j = 0; j < i; j++) 
			if(arr[j] < arr[i])
				dp2[i] = max(dp2[i], dp2[j] + 1);
	}
	
	int mmax = -1;
	reverse(dp2, dp2 + n);
	for(int i = 0; i < n; i++)
		mmax = max(mmax, dp1[i] + dp2[i]);

	cout << mmax - 1;
	return 0;
}

