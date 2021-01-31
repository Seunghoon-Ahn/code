#include <bits/stdc++.h>
using namespace std;
int K, N;
vector <int> v;

int main(void) {
	int tmp;
	long long sum = 0;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> K >> N;
	for(int i = 0; i < K; i++) {
		cin >> tmp;
		v.push_back(tmp);
		sum += tmp;
	}
	long long mid;
	long long max = sum / N + 1;
	long long min = 0;
	while(1) {
		long long total = 0;
		mid = (max + min) / 2;
		if(mid == min) break;
		for(int i = 0; i < K; i++)
			total += v[i] / mid;

		if(total >= N)
			min = mid;
		else if (total < N)
			max = mid;
	}
	cout << mid << '\n';
	return 0;
}
