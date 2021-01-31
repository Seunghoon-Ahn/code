#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 987654321

typedef std::pair<std::pair<int, int>, std::pair<int, int>> Node;

int N;
int M;
int K;
std::priority_queue<Node> pq;
Node node;
int max;
int max_list[310];
std::vector<Node> edges[310];
std::pair<int, int> p;

int main() {
	scanf("%d %d %d", &N, &M, &K);

	node.first.second = 0;
	for (int k = 0; k < K; k++) {
		scanf("%d %d %d", &node.second.first, &node.second.second, &node.first.first);

		if (node.second.first < node.second.second)
			edges[node.second.first].push_back(node);
	}

	for (Node n : edges[1]) {
		n.first.second = 2;
		pq.push(n);
	}

	while (!pq.empty()) {
		Node node = pq.top();
		pq.pop();

		if (max_list[node.second.second] < node.first.first) {
			max_list[node.second.second] = node.first.first;

			// 여행 도시 갯수가 남은 경우
			if (node.first.second < M) {
				Node n2;
				for (Node n : edges[node.second.second]) {
					n2.first.first = node.first.first + n.first.first;
					n2.first.second = node.first.second + 1;
					n2.second = n.second;

					pq.push(n2);
				}
			}
		}
	}

	printf("%d", max_list[M]);
	return 0;
}
/*
3 3 5
1 3 10
1 2 5
2 3 3
1 3 4
3 1 100

3 3 5
1 3 1
1 2 5
2 3 3 
1 3 4
3 1 100

4 4 6
1 3 6
1 2 2
2 3 3
3 4 4
2 4 10
3 2 100

*/