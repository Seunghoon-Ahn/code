#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 192000;
int N, T;
int res[MAX_N];

void init(void) {
	res[0] = 0;
	res[1] = 1;
	res[2] = 2;
	for(int i = 3; i < MAX_N; i++)
		res[i] = (res[i-1] + res[i-2]) % 1000000007;

	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	init();
	cin >> T;
	while(T--) {
		cin >> N;
		cout << res[N] << '\n';
	}
	return 0;
}

