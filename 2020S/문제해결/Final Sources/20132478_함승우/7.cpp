#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 1005;
const int INF = 1 << 30;

vector < pair <int, int> > p[MAX];
vector <int> dijkstra(int start, int vertex);

int N, M;

int main()
{
	int from, to, cost, s, e;
	cin >> N;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> from >> to >> cost;
		p[from].push_back({ to, cost });
	}

	cin >> s >> e;
	vector <int> r = dijkstra(s, N);
	cout << r[e];
}

vector <int> dijkstra(int start, int vertex)
{
	vector <int> dist(vertex + 1, INF);
	dist[start] = 0;

	priority_queue < pair <int, int> > pq;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int now = pq.top().second;
		pq.pop();

		if (dist[now] < cost)
			continue;

		int size = p[now].size();
		for (int i = 0; i < size; i++) {
			int next = p[now][i].first;
			int next_dist = p[now][i].second + cost;

			if (dist[next] > next_dist) {
				dist[next] = next_dist;
				pq.push({ -next_dist, next });
			}
		}
	}
	return dist;
}