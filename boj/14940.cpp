#include <bits/stdc++.h>
using namespace std;
int mmap[1002][1002];
typedef pair<int, int> pp;
queue <pp> q;
int n, m;
int sx, sy;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void bfs(void) {
	q.push({sx, sy});
	while(!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for(int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if(0 <= nx && nx < n && 0 <= ny && ny < m) {
				if(mmap[nx][ny] == 1) {
					mmap[nx][ny] = mmap[cx][cy] + 1;
					q.push({nx, ny});
				}
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> mmap[i][j];
			if(mmap[i][j] == 2) {
				sx = i;
				sy = j;
			}
		}
	}
	
	bfs();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(mmap[i][j])
				cout << mmap[i][j] - 2 << ' ';
			else
				cout << 0 << ' ';
		}
		cout << '\n';
	}
	return 0;
}



