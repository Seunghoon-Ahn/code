#include <bits/stdc++.h>
using namespace std;
long long times[100003];
int N, M;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 0; i < N; i++)
		cin >> times[i];
	sort(times, times + N);
	long long lo = 0;
	long long hi = M * times[N-1];
	long long res = M * times[N-1];

	while(lo <= hi) {
		long long mid = (lo + hi) / 2;
		long long sum = 0;
		for(int i = 0; i < N; i++)
			sum += mid / times[i];
		if(sum >= M) {
			res = min(res, mid);
			hi = mid - 1;
		}
		else
			lo = mid + 1;
	}
	cout << res << '\n';
	return 0;
}


