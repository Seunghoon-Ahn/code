#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

#define INF 987654321

int N, M, A, B;

std::vector<int> graph[110];
std::vector<int> invert_graph[110];
int count;
int max;
int visit[110];
int v[110];

int DFS(int n) {
	if (v[n])
		return 0;

	v[n] = 1;

	for (int to : graph[n]) {
		if (!visit[to]) {
			visit[to] = 1;
			return 1;
		}
	}

	for (int to : graph[n]) {
		for (int from : invert_graph[to]) {
			if (visit[from] && DFS(from)) {
				return 1;
			}
		}
	}

	return 0;
}

int main() {
	scanf("%d %d", &N, &M);

	for (int m = 0; m < M; m++) {
		scanf("%d %d", &A, &B);
		graph[A].push_back(B);
		invert_graph[B].push_back(A);
	}

	for (int n = 1; n <= N; n++) {
		memset(v, 0, sizeof(v));

		int z = DFS(n);
		if (z)
			count++;

	}

	printf("%d", count);
	return 0;
}
/*
5 5
1 1
2 2 
3 3 
4 4 
5 5

5 13
1 2
1 3
2 2 
2 3
3 1
3 2
4 1
4 2
5 1
5 2
5 3
5 4 
5 5

5 11
1 1
1 2
1 4
2 3
2 4
3 2
3 4
4 3
4 5
5 3
5 5

*/