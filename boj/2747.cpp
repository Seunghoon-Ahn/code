#include <bits/stdc++.h>
using namespace std;
int f[47];
int main(void) {
	int n;
	cin >> n;
	f[0] = 0;
	f[1] = 1;
	for(int i = 2;  i < n + 1; i++) {
		f[i] = f[i-2]+f[i-1];
	}
	cout << f[n];
	return 0;
}

