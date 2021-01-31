#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define P pair<long long,int>
using namespace std;

const int MN = 1010;
const long long INF = 1e18;

vector<P> g[MN];
long long dist[MN];

struct cmp {
	bool operator ()(P a, P b) {
		if (a.first == b.first)
			return a.second > b.second;
		return a.first > b.first;
	}
};

int main(void)
{
	ios::sync_with_stdio(false);	cin.tie(NULL);
	int N, M;	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, c;	cin >> a >> b >> c;
		g[a].push_back({ c, b });
	}
	int U, V;	cin >> U >> V;

	fill(dist, dist + MN, INF);
	priority_queue<P, vector<P>, cmp> pq;	pq.push({ 0, U });
	dist[U] = 0;
	while (!pq.empty()) {
		P top = pq.top();	pq.pop();
		long long cur_w = top.first;
		int cur = top.second;
		
		if (dist[cur] < cur_w) continue;

		for (P edge : g[cur]) {
			long long nxt_w = edge.first;
			int nxt = edge.second;
			if (dist[nxt] > cur_w + nxt_w) {
				dist[nxt] = cur_w + nxt_w;
				pq.push({ dist[nxt], nxt });
			}
		}
	}

	cout << dist[V];
}