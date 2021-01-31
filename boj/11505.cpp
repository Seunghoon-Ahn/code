#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MN = 1010101;
const int divi = 1e9+7;
ll seg[MN * 4];
ll N, M, K;

ll update(int idx, ll val, int n, int l, int r) {
	if(r < idx || idx < l)
		return seg[n];
	if(l == r)
		return seg[n] = val;
	int mid = (l + r) / 2;
	return seg[n] = ((update(idx, val, n * 2, l, mid) % divi)  * (update(idx, val, n*2 +1, mid+1, r) % divi)) % divi;
}

ll query(int L, int R, int n, int l, int r) {
	if(r < L || R < l)
		return 1;
	if(L <= l && r <= R)
		return seg[n];
	int mid = (l+r) /2;
	return ((query(L, R, n*2, l, mid) % divi) * (query(L, R, n*2+1, mid+1, r) % divi)) % divi;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;
	int tmp;
	for(int i = 1; i <= N; i++) {
		cin >> tmp;
		update(i, tmp, 1, 1, N);
	}
	int a, b, c;
	for(ll i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if(a == 1)
			update(b, c, 1, 1, N);
		else {
			cout << query(b, c, 1, 1, N) << '\n';
		}
	}
	return 0;
}



