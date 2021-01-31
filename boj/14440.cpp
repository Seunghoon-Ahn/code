#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
#define MOD 100
#define mat vector<vector<ll>>
using namespace std;
long long N, B;

mat multi(mat a, mat b) {
	mat c(a.size(), vector<ll>(b[0].size(), 0));
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < b[0].size(); j++) {
			for(int k = 0; k < b.size(); k++) {
				c[i][j] += a[i][k] * b[k][j];
				c[i][j] %= MOD;
			}
		}
	}
	return c;
}

mat pw(mat a, long long n) {
	if(n == 1)
		return a;
	if(n % 2)
		return multi(pw(a, n-1), a);
	mat tmp = pw(a, n/2);
	return multi(tmp, tmp);
}

int main(void) {
	int x, y;
	string aa;
	string bb;
	N = 2;
	cin >> x >> y;
	cin >> aa >> bb;
	int tmp1 = (aa[0] - '0') * 10 + aa[1] - '0';
	int tmp2 = (bb[0] - '0') * 10 + bb[1] - '0';
	cin >> B;
	if(B == 0) {
		cout << aa << '\n';
		return 0;
	}
	if(B == 1) {
		cout << bb << '\n';
		return 0;
	}

	mat A(N, vector<ll>(N, 0));

	A[0][0] = x;
	A[0][1] = y;
	A[1][0] = 1;
	A[1][1] = 0;
	A = pw(A, B-1);
	cout << ((A[0][0] * tmp2)%MOD + (A[0][1] * tmp1)%MOD)%MOD << '\n';
	return 0;
}
