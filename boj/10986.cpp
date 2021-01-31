#include <bits/stdc++.h>
using namespace std;
long long N, M;
long long arr[1010101];
long long res[1010101];
long long sav[1010];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		cin >> arr[i];
		res[i] = (res[i-1] + arr[i]) % (long long)M;
	}

	for(int i = 1; i <= N; i++)
		sav[res[i]]++;

	long long fin = 0;
	for(int i = 0; i < M; i++)
		fin += (sav[i] * (sav[i] - 1)) / 2L;
	cout << fin  + sav[0] << '\n';
	return 0;
}

