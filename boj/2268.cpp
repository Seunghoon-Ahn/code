#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MN = 1010101;
ll seg[MN * 4];
ll N, M;

ll update(int idx, ll val, int n, int l, int r) {
	if(r < idx || idx < l)
		return seg[n];
	if(l == r)
		return seg[n] = val;
	int mid = (l + r) / 2;
	return seg[n] = update(idx, val, n * 2, l, mid) + update(idx, val, n*2 +1, mid+1, r);
}

ll query(int L, int R, int n, int l, int r) {
	if(r < L || R < l)
		return 0;
	if(L <= l && r <= R)
		return seg[n];
	int mid = (l+r) /2;
	return query(L, R, n*2, l, mid) + query(L, R, n*2+1, mid+1, r);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	int a, b, c;
	for(int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if(a == 1)
			update(b, c, 1, 1, N);
		else {
			if(b > c)
				swap(b, c);
			cout << query(b, c, 1, 1, N) << '\n';
		}
	}
	return 0;
}



