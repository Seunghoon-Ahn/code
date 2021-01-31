#include <bits/stdc++.h>
using namespace std;
int n, m;
int par[1010101];
int rank[1010101];
void init(int n) {
	for(int i = 1; i <= n; i++) {
		par[i] = i;
		rank[i] = 1;
	}
}

int find(int x) {
	if(par[x] == x)
		return x;
	return par[x] = find(par[x]);
}

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return;
	if(rank[x] > rank[y])
		swap(x, y);
	par[x] = y;
	if(rank[x] == rank[y])
		rank[y]++;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	init(n);
	for(int i = 0; i < m; i++) {
		int q, a, b;
		cin >> q >> a >> b;
		if(q) {
			if(find(a) == find(b))
				cout << "YES" << '\n';
			else
				cout << "NO" << '\n';
		}
		else
			unite(a, b);
	}
}

