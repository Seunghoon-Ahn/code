#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

#define MAX_N 301
using namespace std;
using pii = pair<int, int>;
using lint = long long;
int N, M, K;
vector<pii> adj[MAX_N];
lint dist[MAX_N];
int cnt[MAX_N];
lint ans;

void input() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		if (u < v) {
			bool isExist = false;
			for (auto &edge : adj[u]) {
				int nextV = edge.first;
				if (nextV == v) {
					isExist = true;
					if (edge.second < w) {
						edge.second = w;
					}
				}
			}
			if (!isExist) {
				adj[u].push_back({ v, w });
			}
		}
	}
}

void init() {
	memset(dist, 0, sizeof(dist));
	memset(cnt, 0, sizeof(cnt));
}

void bfs(int start) {
	queue<int> q;
	q.push(start);

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (auto edge : adj[now]) {
			int v = edge.first;
			int w = edge.second;

			// 가중치도 더 크고, 포함했을때 개수가 M보다 작고
			if (dist[v] < dist[now] + w && (cnt[v] + 1 <= M)) {
				dist[v] = dist[now] + w;
				cnt[v] += 1;
				q.push(v);
			}
		}
	}
}


void output() {
	printf("%lld", dist[N]);
}

int main() {
	input();
	bfs(1);
	output();
}