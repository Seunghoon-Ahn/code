#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pp;
queue <pp> q;
int box[1002][1002];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int M, N;

void bfs(void) {
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(0 <= nx && nx < N && 0 <= ny && ny < M) {
				if(!box[nx][ny]) {
					box[nx][ny] = box[x][y] + 1;
					q.push({nx, ny});
				}
			}
		}
	}
}

int main(void) {
	cin >> M >> N;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++) {
			cin >> box[i][j];
			if(box[i][j] == 1)
				q.push({i, j});
		}

	bfs();
	int day = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(box[i][j] == 0) {
				cout << -1 << '\n';
				return 0;
			}
			if(day < box[i][j])
				day = box[i][j];
		}
	}
	cout << day - 1 << '\n';
	return 0;
}

