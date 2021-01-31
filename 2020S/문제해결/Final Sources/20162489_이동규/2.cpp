#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 1000000001

int N;
int M;
int T[100010];
long long result;
std::priority_queue<std::pair<long long, int>> pq;
std::pair<long long, int> p;


int main() {
	scanf("%d %d", &N, &M);

	for (int n = 0; n < N; n++) {
		scanf("%d", &T[n]);
		p.first = -T[n];
		p.second = n;
		pq.push(p);
	}

	for (int m = 0; m < M; m++) {
		p = pq.top();
		pq.pop();

		result = std::max(result, -p.first);

		p.first -= T[p.second];
		pq.push(p);
	}

	printf("%lld", result);
	return 0;
}
/*
2 6
7
10

7 10
3
8
3
6
9
2
4

1 1000000000
1

8 1000000000
1
1
1
1
1
1
1
1

*/