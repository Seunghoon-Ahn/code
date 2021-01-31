#include <bits/stdc++.h>

using namespace std;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main(void)
{
	int s1, p1;
	int s2, p2;
	int rs, rp;
	int lcm, rgcd;
	cin >> s1 >> p1;
	cin >> s2 >> p2;

	lcm = p1 * p2 / gcd(p1, p2);
	rp = lcm;
	rs = s1 * (lcm / p1) + s2 * (lcm / p2);
	rgcd = gcd(rp, rs);
	rp = rp / rgcd;
	rs = rs / rgcd;
	cout << rs << ' ' << rp;
	return 0;
}
