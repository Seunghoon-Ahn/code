#include <bits/stdc++.h>
using namespace std;
int n, par[300003];

int init(int num) {
	for(int i = 1; i <= num; i++) {
		par[i] = i;
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
	par[x] = y;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp1, tmp2;
	cin >> n;
	init(n);
	if(n == 2) {
		cout << "1 2\n";
		return 0;
	}
	for(int i = 0; i < n-2; i++) {
		cin >> tmp1 >> tmp2;
		unite(tmp1, tmp2);
	}
	int f1 = find(1);
	for(int i = 2; i <= n; i++) {
		int tmp = find(i);
		if(f1 != tmp) {
			cout << 1 << ' ' << i << '\n';
			break;
		}
	}
	return 0;
}
	
