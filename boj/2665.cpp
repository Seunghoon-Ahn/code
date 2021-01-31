#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <string>
#include <functional>
using namespace std;
int map[53][53];
int visit[53][53];
int n;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			scanf("%1d", &map[i][j]);
			visit[i][j] = 987654321;
		}
	queue<pair<int, int>> q;
	q.push({0, 0});
	visit[0][0] = 0;
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(0 <= nx && nx < n && 0 <= ny && ny < n) {
				if(map[nx][ny]) {
					if(visit[nx][ny] > visit[x][y]) {
						visit[nx][ny] = visit[x][y];
						q.push({nx, ny});
					}
				}
				else {
					if(visit[nx][ny] > visit[x][y] + 1) {
						visit[nx][ny] = visit[x][y] + 1;
						q.push({nx, ny});
					}
				}

			}
		}
	}
	cout << visit[n - 1][n - 1] << '\n';
	return 0;
}
