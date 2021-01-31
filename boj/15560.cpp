#include <bits/stdc++.h>
using namespace std;

int n, q, u, v, arr[1004];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> q >> u >> v;
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
		arr[i] = u * arr[i] + v;
	}
	while(q--) {
		int c, a, b;
		cin >> c >> a >> b;
		if(!c) {
			int res = -1e9;
			int sum = -1e9;
			for(int i = a; i <= b; i++)
				res = max(res, sum = max(sum, 0) + arr[i]);
			cout << res - v << '\n';
		}
		else
			arr[a] = u * b + v;
	}
	return 0;
}
