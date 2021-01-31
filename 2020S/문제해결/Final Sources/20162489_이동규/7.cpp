#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

#define INF 987654321

typedef std::pair<int, std::pair<int, int>> Node;

int N, M;
int S, E;

std::vector<Node> edges[1010];
Node node;
std::priority_queue<Node> pq;
int min[1010];

int main() {
	scanf("%d %d", &N, &M);
	for (int m = 0; m < M; m++) {
		scanf("%d %d %d", &node.second.first, &node.second.second, &node.first);
		node.first = -node.first;
		edges[node.second.first].push_back(node);
	}

	scanf("%d %d", &S, &E);

	for (int n = 1; n <= N; n++) {
		min[n] = INF;
	}

	min[S] = 0;
	for (Node n : edges[S]) {
		pq.push(n);
	}

	while (!pq.empty()) {
		node = pq.top();
		pq.pop();

		if (min[node.second.second] <= -node.first) {
			continue;
		}
		min[node.second.second] = -node.first;

		for (Node n : edges[node.second.second]) {
			n.first -= min[node.second.second];
			pq.push(n);
		}
	}

	printf("%d", min[E]);
	return 0;
}
/*
5
8
1 2 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1 
3 5 1
4 5 3
1 5

2
1
1 2 0
1 2

5
9
1 2 4
1 3 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1
3 5 1
4 5 3
1 5

*/