#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M;
const int MN = 101010;
const int INF = 2100000000;
ll seg[MN * 4];
ll update(int idx, ll val, int n, int l, int r) {
	if( r < idx || idx < l)
		return seg[n];
	if(l == r)
		return seg[n] = val;
	int mid = (l + r) /2;
	return seg[n] = min(update(idx, val, n * 2, l, mid), update(idx, val, n*2+1, mid+1, r));
}

ll query(int L, int R, int n, int l, int r) {
	if(r < L || R < l)
		return INF;
	if(L <= l && r <= R)
		return seg[n];
	int mid = (l + r) /2;
	return min(query(L, R, n*2, l, mid), query(L, R, n*2+1, mid+1, r));
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int tmp;
	for(int i = 1; i <= N; i++) {
		cin >> tmp;
		update(i, tmp, 1, 1, N);
	}
	cin >> M;
	int tmp1, tmp2, tmp3;
	for(int i = 1; i <= M; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		if(tmp1 == 1)
			update(tmp2, tmp3, 1, 1, N);
		else
			cout << query(tmp2, tmp3, 1, 1, N) << '\n';
	}
	return 0;
}

