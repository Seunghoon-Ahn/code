#include <bits/stdc++.h>
using namespace std;

int solve(int a, int b) {
	int res = 1;
	while(b >= 1) {
		if(b & 1)
			res = (1LL * res * a) % 1000000007;
		b >>= 1;
		a = (1LL * a * a) % 1000000007;
	}
	return res;
}

int main(void) {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		cout << solve(2, n-2) << '\n';
	}
	return 0;
}
