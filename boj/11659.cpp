#include <bits/stdc++.h>
using namespace std;
int arr[101010];
int sum[101010];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int N, M;
	int tmp1, tmp2;
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		cin >> arr[i];
		sum[i] = sum[i-1] + arr[i];
	}
	for(int i = 0; i < M; i++) {
		cin >> tmp1 >> tmp2;
		cout << sum[tmp2] - sum[tmp1-1] << '\n';
	}
	return 0;
}

