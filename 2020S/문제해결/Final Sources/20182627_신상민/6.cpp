#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int n, m, k;
int map[100][100];
int visited[100][100];
int t;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

queue<pair<int, int>> q;
queue<pair<int, int>> cq;

// bfs와 cheeseBfs 만들기
// queue와 cheeseQueue만들기
// visited 로 방문했는지 판별

void bfs() {
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		visited[y][x] = 1;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nextY = y + dy[i];
			int nextX = x + dx[i];
			if (nextY >= 0 && nextY <= n && nextX >= 0 && nextX <= m) {
				if (visited[nextY][nextX] == 0) {
					visited[nextY][nextX] = 1;
					if (map[nextY][nextX] == 0)
						q.push(make_pair(nextY, nextX));
					else {
						cq.push(make_pair(nextY, nextX));
					}
				}
			}
		}
	}
}

void cheeseBfs() {
	int size = cq.size();
	t++;
	while (size--) {
		int y = cq.front().first;
		int x = cq.front().second;
		cq.pop();
		int cnt = 0;
		for (int i = 0; i < 4; i++) {
			int nextY = y + dy[i];
			int nextX = x + dx[i];
			if (visited[nextY][nextX] == 1 && map[nextY][nextX] == 0) {
				cnt++;
			}
		}
		if (cnt >= 2) {
			map[y][x] = 0;
			visited[y][x] = 0;
			q.push(make_pair(y, x));
		}
		else {
			cq.push(make_pair(y, x));
		}
	}
}

int main() {
	cin >> n >> m; //세로, 가로
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	q.push(make_pair(0, 0));
	visited[0][0] = 1;
	while (!q.empty()) {
		//bfs
		bfs();

		if (cq.empty())
			break;
		//cheeseBfs
		cheeseBfs();
	}
	cout << t << '\n';
	return 0;
}