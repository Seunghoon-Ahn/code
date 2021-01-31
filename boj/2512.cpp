#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
vector <ll> m;
int total;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp;
	int mmax;
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> tmp;
		m.push_back(tmp);
		if(i == 0)
			mmax = tmp;
		
		if(mmax < tmp)
			mmax = tmp;
	}
	cin >> total;
	sort(m.begin(), m.end());
	int mid;
	int min = 0, max = mmax + 1;
	while(1) {
		long long sum = 0;
		mid = (min + max) / 2;
		if(mid == min)
			break;
		for(int i = 0 ; i < N; i++) {
			if(m[i] <= mid)
				sum += m[i];
			else if(m[i] > mid)
				sum += mid;
		}
		if(sum > total)
			max = mid;
		if(sum <= total)
			min = mid;
	}
	cout << mid << '\n';
	return 0;
}
