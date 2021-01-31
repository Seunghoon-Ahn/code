#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdlib>
#include<vector>

#define NODE 1005

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int INF = 1e9;
bool visited[NODE];
int dist[NODE];
vector<pii> G[NODE];
int N, M;
int st, ed;
void Dijkstra(int s, int e)
{
	fill(dist, dist + NODE, INF);
	priority_queue<pii, vector<pii>, greater<vector<pii>>> pq;
	pq.push({ 0, s });
	visited[s] = true;
	while (!pq.empty())
	{
		pii curr = pq.top();
		pq.pop();
		int currVal = curr.second;
		for (auto at : G[currVal])
		{
			int next = at.second;
			int weight = at.first;
			if (visited[next])
				continue;
			visited[next] = true;
			if (dist[currVal] != INF && dist[next] > dist[currVal] + weight)
			{
				dist[next] = dist[currVal] + weight;
				pq.push({ dist[next], next });
			}
		}
	}

	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0, u, v, w; i < M; ++i)
	{
		cin >> u >> v >> w;
		G[u].push_back({ w, v });
	}

	cin >> st >> ed;

	Dijkstra(st, ed);
	cout << dist[ed] << '\n';

	return 0;
}