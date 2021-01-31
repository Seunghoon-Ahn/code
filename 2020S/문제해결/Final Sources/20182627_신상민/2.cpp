#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

long long n, m;
long long t[100000];

bool isOk(int inTime) {
	long long canP = 0;
	for (int i = 0; i < n; i++) {
		canP += inTime / t[i];
	}
	if (canP >= m) {
		return true;
	}
	return false;
}

int main() {
	long long low = 0;
	long long upper = 1000000000;
	long long mid;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> t[i];
		upper = min(upper, t[i]);
	}
	low = upper;
	upper = upper * m;
	mid = (upper + low) / 2;

	while (low != upper) {
		if (isOk(mid)) {
			upper = mid;
		}
		else {
			low = mid + 1;
		}
		mid = (upper + low) / 2;
		//cout <<  low << ", "<< mid << ", " << upper << '\n';
	}
	cout << low << '\n';
	return 0;
}