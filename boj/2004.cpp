#include <bits/stdc++.h>
using namespace std;

long long five = 0, two = 0;
long long n, m;

void divide(long long a) {
	for(long long i = 2; i <= a; i *= 2)
		two += a / i;
	for(long long i = 5; i <= a; i *= 5)
		five += a / i;
}

void divide2(long long a) {
	for(long long i = 2; i <= a; i *= 2)
		two -= a / i;
	for(long long i = 5; i <= a; i *= 5)
		five -= a / i;
}

int main(void) {
	cin >> n >> m;
	
	if(n == m || m == 0) {
		cout << 0;
		return 0;
	}
	
	divide(n);
	divide2(m);
	divide2(n-m);
	
	cout << min(five, two) << '\n';

	return 0;
}
