#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
#define MOD 1000000
#define mat vector<vector<ll>>
using namespace std;
long long B;

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
	N = 2;
	cin >> B;
	mat A(N, vector<ll>(N, 0));

	A[0][0] = 1;
	A[0][1] = 1;
	A[1][0] = 1;
	A[1][1] = 0;
	A = pw(A, B-1);
	cout << A[0][0] % MOD << '\n';
	return 0;
}
