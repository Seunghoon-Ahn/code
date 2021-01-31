#include <bits/stdc++.h>
using namespace std;
int a, b, c, d, e, f;

int main(void) {
	int x, y;
	cin >> a >> b >> c >> d >> e >> f;
	if (a == 0 || d == 0) {
		
	
	}
	x = ((c * e) - (f * b)) / ((a * e) - (d * b));
	y = (c - (a * x)) / b;
	cout << x << ' ' << y << '\n';
	return 0;
}
