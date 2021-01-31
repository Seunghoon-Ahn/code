#include <bits/stdc++.h>
using namespace std;
int T, N;
vector<int> v(1004);

int solve(int L, int R) {
	if(L == R)
		return v[L];
	int mid = (L+R)/2;
	int ret = max(solve(L, mid), solve(mid+1, R));
	int lo = mid;
	int hi = mid+1;
	int minV = min(v[lo], v[hi]);
	int sum = v[lo] + v[hi];
	ret = max(ret, sum);
	while(L < lo || hi < R) {
		if(L < lo && (R == hi || v[lo-1] > v[hi+1])) {
			--lo;
			sum += v[lo];
			minV = (minV, v[lo]);
		}
		else {
			++hi;
			sum += v[hi];
			minV = min(minV, v[hi]);
		}
		ret = max(ret, sum);
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	while(T--) {
		int tmp;
		cin >> N;
		v.clear();
		v.push_back(0);
		for(int i = 0; i < N; i++) {
			cin >> tmp;
			v.push_back(tmp);
		}
		cout << solve(1, N) << '\n';
	}
	return 0;
}
