#include <bits/stdc++.h>
long long max(long long a, long long b) {
	return a < b ? b : a;
}
long long min(long long a, long long b) {
	return a < b ? a : b;
}

using namespace std;
int N;
vector <long long> v;

long long calcul(long long a, long long b) {
	long long tmp = 0;
	for(int i = a; i <= b; i++)
		tmp += v[a];

	return tmp;
}

long long height(long long a, long long b) {
	long long mininum = v[a];
	for(int i = a; i <= b; i++)
		if(mininum > v[i])
			mininum = v[i];
	return mininum;
}

long long dnc(int L, int R) {
	if(L == R)
		return v[L] * v[L];
	long long mid = ( L + R ) / 2;
	long long ret = max(dnc(L, mid), dnc(mid+1, R));
	long long l = mid;
	long long r = mid + 1;
	long long h = min(v[l], v[r]);
	long long sum = v[l] + v[r];
	ret = max(ret, h * sum);
	while(L < l || r < R) {
		if(L < l && (R == r || v[l-1] > v[r+1])) {
			--l;
			sum += v[l];
			h = min(h, v[l]);
		}
		else {
			++r;
			sum += v[r];
			h = min(h, v[r]);
		}
		ret = max(ret, sum * h );
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
