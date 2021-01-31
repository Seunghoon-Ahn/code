#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

#define INF 987654321

int N, M;
int map[110][110];
int count;
int total_time;

int direction[4][2] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};

int visit[110][110];
int meltspot[110][110];

void check_air() {
	std::queue<std::pair<int, int>> q;
	std::pair<int, int> p;

	memset(visit, 0, sizeof(visit));
	p.first = 0;
	p.second = 0;
	q.push(p);
	visit[0][0] = 1;
	map[0][0] = 2;

	while (!q.empty()) {
		p = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int y = p.first + direction[i][0];
			int x = p.second + direction[i][1];

			if (y < 0 || y >= N || x < 0 || x >= M || visit[y][x] || map[y][x] == 1)
				continue;

			std::pair<int, int> p2;
			p2.first = y;
			p2.second = x;
			q.push(p2);

			visit[y][x] = 1;
			map[y][x] = 2;
		}
	}
}

void melt(int y, int x) {
	std::pair<int, int> p = { y, x };
	std::queue<std::pair<int, int>> q;

	q.push(p);

	while (!q.empty()) {
		p = q.front();
		q.pop();

		if (visit[p.first][p.second])
			continue;

		visit[p.first][p.second] = 1;

		for (int i = 0; i < 4; i++) {
			int y = p.first + direction[i][0];
			int x = p.second + direction[i][1];

			if (y < 0 || y >= N || x < 0 || x >= M)
				continue;

			if (map[y][x] == 2) {
				meltspot[p.first][p.second]++;
				continue;
			}

			if (map[y][x] != 1 || visit[y][x])
				continue;

			std::pair<int, int> p2 = { y, x };
			q.push(p2);
		}
	}

}

int main() {
	scanf("%d %d", &N, &M);
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			scanf("%d", &map[n][m]);
			if (map[n][m] == 1)
				count++;
		}
	}

	while (count > 0) {
		check_air();

		memset(visit, 0, sizeof(visit));
		memset(meltspot, 0, sizeof(meltspot));

		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				if (map[n][m] == 1 && !visit[n][m]) {
					melt(n, m);
				}
			}
		}

		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				if (meltspot[n][m] >= 2) {
					count--;
					map[n][m] = 0;
				}
			}
		}

		total_time++;
	}

	printf("%d", total_time);
	return 0;
}
/*
8 9
0 0 0 0 0 0 0 0 0
0 0 0 1 1 0 0 0 0
0 0 0 1 1 0 1 1 0
0 0 1 1 1 1 1 1 0
0 0 1 1 1 1 1 0 0
0 0 1 1 0 1 1 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0

8 9
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 1 1 0 0 0 1 1 0
0 1 0 1 1 1 0 1 0
0 1 0 0 1 0 0 1 0
0 1 0 1 1 1 0 1 0
0 1 1 0 0 0 1 1 0
0 0 0 0 0 0 0 0 0


9 9
0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 0
0 1 0 0 0 0 0 1 0
0 1 0 0 1 0 0 1 0
0 1 0 1 0 1 0 1 0
0 1 0 0 1 0 0 1 0
0 1 0 0 0 0 0 1 0
0 1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 0 0

*/