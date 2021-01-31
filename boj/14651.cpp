#include <bits/stdc++.h>
using namespace std;
int N;
const int DIV_N = 1000000009;
int res[33339];

int main(void) {
	cin >> N;
	res[2] = 2;
	for(int i = 3; i <= N; i++)
		res[i] = (res[i-1] * 3) % DIV_N;
	cout << res[N] << '\n';
	return 0;
}
