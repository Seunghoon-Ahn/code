#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

void printEdges(vector<vector<pair<int, int>>> &edges) {
	for (int i = 1; i < edges.size(); i++) {
		printf("\n%d\n", i);
		for (int j = 0; j < edges[i].size(); j++) {
			printf("(%d %d)  ", edges[i][j].first, edges[i][j].second);
		}

	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<pair<int, int>>> edges(n + 1);
	int a, b, c;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(make_pair(b, c));
	}
	int start, end;
	scanf("%d %d", &start, &end);
	int answer = 10000000;
	int visited = 0;
	queue<pair<int, int>> q;
	q.push(make_pair(start, 0));
	while (!q.empty()) {
		int cur = q.front().first;
		int cur_cost = q.front().second;
		if (cur == end) {
			if (answer > cur_cost) {
				answer = cur_cost;
			}
		}
		q.pop();
		visited |= 1 << cur;
		for (int i = 0; i < edges[cur].size(); i++) {
			int next = edges[cur][i].first;
			int cost = edges[cur][i].second;
			if (visited & (1 << next)) continue;
			q.push(make_pair(next, cur_cost + cost));
		}
	}
	printf("%d", answer);
	return 0;
}