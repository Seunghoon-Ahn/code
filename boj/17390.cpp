#include <bits/stdc++.h>
using namespace std;
int N, Q;
long long num[300003];
long long sum[300003];
int main(void) {
	int tmp1, tmp2;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> Q;
	for(int i = 1; i <= N; i++) {
		cin >> num[i];
	}
	sort(num + 1, num + N + 1);
	for(int i = 1; i <= N; i++)
		sum[i] = sum[i-1] + num[i];
	for(int i = 0; i < Q; i++) {
		cin >> tmp1 >> tmp2;
		cout << sum[tmp2] - sum[tmp1-1] << '\n';
	}
	return 0;
}


