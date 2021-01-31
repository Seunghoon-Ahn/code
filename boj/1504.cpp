#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
typedef pair<int, int> pp;
vector <pp> vec[803];
int N, E;
int v1, v2;
const int INF = 800003;
priority_queue <pp> pq;
int d[803]; //마지막에는 v1 기준
int from1[803];
int fromn[803];

void dij(int st) {
	fill(d + 1, d + 1 + N, INF);
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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> E;
	for(int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		vec[a].push_back({c, b});
		vec[b].push_back({c, a});
	}
	cin >> v1 >> v2;
	
	dij(1);
	for(int i = 1; i <= N; i++)
		from1[i] = d[i];
	dij(N);
	for(int i = 1; i <= N; i++)
		fromn[i] = d[i];
	dij(v1);
	int r1, r2;
	r1 = from1[v1] + fromn[v2] + d[v2];
	r2 = from1[v2] + fromn[v1] + d[v2];
	int res = min(r1, r2);
	if(res >= INF)
		cout << -1 << '\n';
	else
		cout << res << '\n';
	return 0;
}

