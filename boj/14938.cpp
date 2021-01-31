#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pp;
int n, m, r;
int item[103];
vector <pp> road[103];
int d[103];
const int INF = 150000;
priority_queue <pp, vector<pp>, greater<pp>> pq;
int sum = 0, maxitem = 0;

void bfs(int st) {
	pq.push({0, st});
	d[st] = 0;

	while(!pq.empty()) {
		pp tmp = pq.top();
		pq.pop();
		int cur_w = tmp.first;
		int cur = tmp.second;
		if(d[cur] < cur_w)
			continue;
		for(pp next : road[cur]) {
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
	int tmp1, tmp2, tmp3;
	cin >> n >> m >> r;
	for(int i = 1; i <= n; i++)
		cin >> item[i];
	for(int i = 0; i < r; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		road[tmp1].push_back({tmp3, tmp2});
		road[tmp2].push_back({tmp3, tmp1});
	}
	for(int i = 1; i <= n; i++) {
		fill(d+1, d+1+n, INF);
		sum = 0;
		bfs(i);
		for(int j = 1; j <= n; j++)
			if(d[j] <= m)
				sum += item[j];
		if(sum > maxitem)
			maxitem = sum;
	}
	cout << maxitem << '\n';
	return 0;
}

