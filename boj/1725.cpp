#include <bits/stdc++.h>
using namespace std;
int N;
vector <int> v;
int dnc(int L, int R) {
	if(L == R)
		return v[L];
	int mid = ( L + R ) / 2;
	int ret = max(dnc(L, mid), dnc(mid+1, R));
	int l = mid;
	int r = mid + 1;
	int h = min(v[l], v[r]);
	ret = max(ret, h * (r - l + 1));
	while(L < l || r < R) {
		if(L == l)
			h = min(h, v[++r]);
		else if (R == r)
			h = min(h, v[--l]);
		else if(v[l-1] > v[r+1])
			h = min(h, v[--l]);
		else
			h = min(h, v[++r]);

		ret = max(ret, h * (r - l + 1));
	}
	return ret;
}
int main(void) {
	int tmp;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	v.push_back(0);
	for(int i = 1; i <= N; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	cout << dnc(1, N);
	return 0;
}

