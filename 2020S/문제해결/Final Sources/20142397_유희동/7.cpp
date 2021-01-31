#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_N 1001
#define INF 0x7f7f7f7f7f7f7f7f
using namespace std;
using pii = pair<int, int>;
using lint = long long;
int N, M;
vector<pii> adj[MAX_N];
lint dist[MAX_N];
int startCity, endCity;
void input() {
	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adj[u].push_back({ v, w });
	}
	scanf("%d %d", &startCity, &endCity);
}

void init() {
	memset(dist, 0x7f, sizeof(dist));
}

void findMinPath() {
	priority_queue<pii> pq;
	dist[startCity] = 0;
	pq.push({ startCity, 0 });

	while (!pq.empty()) {
		pii now = pq.top();
		int u = now.first;
		int cost = now.second;
		pq.pop();

		if (cost > dist[u]) continue;
		
		for (auto next : adj[u]) {
			int v = next.first;
			int w = next.second;

			if (dist[v] > cost + w) {
				dist[v] = cost + w;
				pq.push({ v, dist[v] });
			}
		}
	}
}

void output() {
	printf("%d", dist[endCity]);
}

int main() {
	input();
	init();
	findMinPath();
	output();
}