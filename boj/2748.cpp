#include <bits/stdc++.h>
using namespace std;
long long arr[91];
int main(void) {
	int n;
	cin >> n;
	arr[0] = 0;
	arr[1] = 1;
	for(int i = 2; i < n+1; i++) {
		arr[i] = arr[i-1] +arr[i-2];
	}
	cout << arr[n];
	return 0;
}
