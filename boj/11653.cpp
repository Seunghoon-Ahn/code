#include <bits/stdc++.h>

using namespace std;

int main(void) {
	int a;
	cin >> a;
	for(int i = 2; i * i <= a; i++) {
		while(a % i == 0) {
			cout << i << '\n';
			a /= i;
		}
	}

	if(a > 1)
		cout << a << '\n';

	return 0;
}
