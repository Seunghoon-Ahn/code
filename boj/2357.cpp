#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M;
const int MN = 101010;
const int INF = 2100000000;
ll seg1[MN * 4];
ll seg2[MN * 4];

ll update1(int idx, ll val, int n, int l, int r) {
	if( r < idx || idx < l)
		return seg1[n];
	if(l == r)
		return seg1[n] = val;
	int mid = (l + r) /2;
	return seg1[n] = min(update1(idx, val, n * 2, l, mid), update1(idx, val, n*2+1, mid+1, r));
}

ll update2(int idx, ll val, int n, int l, int r) {
	if(r < idx || idx < l)
		return seg2[n];
	if(l==r)
		return seg2[n] = val;
	int mid = (l + r) /2;
	return seg2[n] = max(update2(idx, val, n*2, l, mid), update2(idx, val, n*2+1, mid+1, r));
}

ll query1(int L, int R, int n, int l, int r) {
	if(r < L || R < l)
		return INF;
	if(L <= l && r <= R)
		return seg1[n];
	int mid = (l + r) /2;
	return min(query1(L, R, n*2, l, mid), query1(L, R, n*2+1, mid+1, r));
}

ll query2(int L, int R, int n, int l, int r) {
	if(r < L || R < l)
		return 0;
	if(L <= l && r <= R)
		return seg2[n];
	int mid = (l+r)/2;
	return max(query2(L, R, n*2, l, mid), query2(L, R, n*2+1, mid+1, r));
}




int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	int tmp;
	for(int i = 1; i <= N; i++) {
		cin >> tmp;
		update1(i, tmp, 1, 1, N);
		update2(i, tmp, 1, 1, N);
	}
	int tmp2, tmp3;
	for(int i = 1; i <= M; i++) {
		cin >> tmp2 >> tmp3;
		cout << query1(tmp2, tmp3, 1, 1, N) << ' ' << query2(tmp2, tmp3, 1, 1, N) << '\n';
	}
	return 0;
}

