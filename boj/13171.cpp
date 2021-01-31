#include <bits/stdc++.h>
using namespace std;
long long a, b, c;
long long pw(long long a, long long n) {
	if(n == 0)
		return 1;
	if(n % 2)
		return ((pw(a, n-1) % c) * (a % c)) % c;
	long long tmp = pw(a, n/2);
	return ((tmp % c) * (tmp % c)) % c;
}

int main(void) {
	cin >> a;
	cin >> b;
	c = 1000000007;
	cout << pw(a, b);
}

