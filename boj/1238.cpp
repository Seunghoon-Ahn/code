#include <bits/stdc++.h>
using namespace std;
vector <pair<int, int>> vec[1003];
int n, m, x;
int d[1003];
int sav[1003];
const int INF = 2e9;

void dij(int st) {
	fill(d + 1, d + 1 + n, INF);
	using pp = pair<int, int>;
	priority_queue<pp, vector<pp>, greater<pp>> pq;
	pq.push({0, st});
	d[st] = 0;

	while(!pq.empty()) {
		pp tmp = pq.top();
		pq.pop();
		int cur_w = tmp.first;
		int cur = tmp.second;
		if(d[cur] < cur_w)
			continue;
		for(pp next : vec[cur]) {
			if(d[next.second] > d[cur] + next.first) {
				d[next.second] = d[cur] + next.first;
				pq.push({d[next.second], next.second});
			}
		}
	}
}

int main(void) {
	int tmp1, tmp2, tmp3;
	cin >> n >> m >> x;
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		vec[tmp1].push_back({tmp3, tmp2});
	}
	
	for(int i = 1; i <= n; i++) {
		dij(i);
		sav[i] = d[x];
	}

	dij(x);
	int mmax = 0;
	for(int i = 1; i <= n; i++) {
		sav[i] += d[i];
		if(mmax < sav[i])
			mmax = sav[i];
	}
	cout << mmax << '\n';
	return 0;
}

