#include <bits/stdc++.h>
using namespace std;
int N, M;
vector <long long> t;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	long long tmp;
	long long max, min = 0;
	cin >> N >> M;
	for(int i = 0; i < N; i++) {
		cin >> tmp;
		t.push_back(tmp);
		if(i == 0) {
			max = tmp;
			//min = tmp;
		}
		else {
			if(tmp > max)
				max = tmp;
		}
	}
	long long mid;

	while(1) {
		mid = (max + min) / 2;
		if(mid == min) break;
		long long tree = 0;
		for(int i = 0; i < N; i++) {
			if(t[i] > mid)
				tree += t[i] - mid;
		}
		if(tree >= M)
			min = mid;
		else if(tree < M)
			max = mid;
		else
			break;
	}
	cout << mid << '\n';

	return 0;
}


	
