#include <bits/stdc++.h>
using namespace std;
int n, m, s;
struct edge{
	int w, v;
};
vector <edge> vec[20003];
int d[20004];
const int INF = 2123456789;

int main(void) {
	//fill(d + 1, d + 1 + n, INF);
	int tmp1, tmp2, tmp3;
	cin >> n >> m;
	cin >> s;
	fill(d + 1, d + 1 + n, INF);
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		vec[tmp1].push_back({tmp3, tmp2});
	}
	using P = pair<int, int>;
	priority_queue<P, vector<P>, greater<P>> pq;
	pq.push({0, s});
	d[s] = 0;

	while(!pq.empty()) {
		P tmp = pq.top();
		pq.pop();
		int cur_w = tmp.first;
		int cur = tmp.second;
		if(d[cur] < cur_w)
			continue;
		for(edge next : vec[cur]) {
			if(d[next.v] > d[cur] + next.w) {
				d[next.v] = d[cur] + next.w;
				pq.push({d[next.v], next.v});
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		if(d[i] == INF)
			cout << "INF\n";
		else
			cout << d[i] << '\n';
	}
	return 0;
}

