#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
#define MOD 1000000007
#define mat vector<vector<ll>>
using namespace std;
long long N, B;

mat multi(mat a, mat b) {
	mat c(a.size(), vector<ll>(b[0].size(), 0));
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < b[0].size(); j++) {
			for(int k = 0; k < b.size(); k++) {
				c[i][j] += (a[i][k] * b[k][j]) % MOD;
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
	N = 8;
	cin >> B;

	mat A = {
		{0, 1, 0, 0, 1, 0 ,0, 0},
		{1, 0, 1, 0, 1, 0, 0, 0},
		{0, 1, 0, 1, 1, 0, 1, 0},
		{0, 0, 1, 0, 0, 1, 1, 0},
		{1, 1, 1, 0, 0, 0, 1, 0},
		{0, 0, 0, 1, 0, 0, 0, 1},
		{0, 0, 1, 1, 1, 0, 0, 1},
		{0, 0, 0, 0, 0, 1, 1, 0}
	};
	mat res = pw(A, B);
	cout << res[0][0];
	return 0;
}
