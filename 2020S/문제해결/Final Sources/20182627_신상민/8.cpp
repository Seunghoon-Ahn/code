#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int n, m, ans;
vector<int> w[101];

int v[101];
int match[101];

bool isP(int a) {
	if (v[a] == 1) {
		return false;
	}
	v[a] = 1;
	for (int i = 0; i < w[a].size(); i++) {
		int b = w[a][i];
		if (match[b] == 0) {
			match[b] = a;
			return true;
		}
	}
	for (int i = 0; i < w[a].size(); i++) {
		int b = w[a][i];
		if (isP(match[b])) {
			match[b] = a;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		w[a].push_back(b);
	}

	for (int i = 1; i <= n; i++) {
		memset(v, 0, sizeof(v));
		if (isP(i)) {
			ans++;
		}
	}
	cout << ans << '\n';

	return 0;
}