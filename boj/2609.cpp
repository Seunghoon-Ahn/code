#include <bits/stdc++.h>

using namespace std;

int main(void) {
	int a, b;
	int sa, sb;
	int gcd, lcm;
	cin >> a >> b;
	sa = a;
	sb = b;

	while(1) {
		int tmp;
		a = a % b;
		if(a == 0) {
			gcd = b;
			break;
		}
		else {
			tmp = a;
			a = b;
			b = tmp;
		}
	}
	cout << gcd << '\n' << sa * sb / gcd;
	return 0;
}
