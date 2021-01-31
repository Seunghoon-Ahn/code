#include <bits/stdc++.h>
using namespace std;
long long X, Y, Z;

int main(void) {
	cin >> X >> Y;
	Z = (Y * 100) / X;

	if(Z >= 99) {
		cout << -1 << '\n';
		return 0;
	}
	long long min = 1;
	long long max = 1e9;
	long long mid;

	while(1) {
		mid = (min + max) / 2;
		if(max < min) break;

		long long newZ = (Y+mid) * 100 / (X+mid);
		if(newZ > Z)
			max = mid - 1;
		else
			min = mid + 1;
	}
	cout << min << '\n';
	return 0;
}

