#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

#define INF 987654321

int N;
int abilities[30][30];
int visit[30];
int result = INF;

void func(int index, int n, int totalN) {
	if (n == totalN) {
		int a = 0;
		int b = 0;
		std::vector<int> team1, team2;

		for (int i = 0; i < totalN * 2; i++) {
			if (visit[i])
				team1.push_back(i);
			else
				team2.push_back(i);
		}

		for (int y : team1) {
			for (int x : team1) {
				a += abilities[y][x];
			}
		}

		for (int y : team2) {
			for (int x : team2) {
				b += abilities[y][x];
			}
		}

		
		result = std::min(result, abs(a - b));
		return;
	}

	for (int i = index; i < totalN * 2; i++) {
		visit[i] = 1;
		func(i + 1, n + 1, totalN);
		visit[i] = 0;
	}
}


int main() {
	scanf("%d", &N);
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf("%d", abilities[y] + x);
		}
	}

	func(0, 0, N / 2);
	printf("%d", result);
	return 0;
}
/*
4
0 1 2 3
4 0 5 6
7 1 0 2 
3 4 5 0

6
0 1 2 3 4 5
1 0 2 3 4 5
1 2 0 3 4 5
1 2 3 0 4 5
1 2 3 4 0 5
1 2 3 4 5 0

8
0 5 4 5 4 5 4 5
4 0 5 1 2 3 4 5
9 8 0 1 2 3 1 2
9 9 9 0 9 9 9 9
1 1 1 1 0 1 1 1
8 7 6 5 4 0 3 2
9 1 9 1 9 1 0 9
6 5 4 3 2 1 9 0


6
0 84 1 1 1 1
84 0 1 1 1 1
1 1 0 8 100 4
1 1 1 0 7 4
1 1 3 10 0 4
1 1 11 2 14 0

*/