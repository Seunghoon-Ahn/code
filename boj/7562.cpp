#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pp;
int m[303][303];
int n, sx, sy, ex, ey;
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void bfs(void) {
	queue<pp> q;
	q.push({sx, sy});
	while(!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();
		if(cx == ex && cy == ey) {
			cout << m[cx][cy] << '\n';
			return;
		}
		for(int i = 0; i < 8; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if(0 <= nx && nx < n && 0 <= ny && ny < n)
				if(!m[nx][ny]) {
					m[nx][ny] = m[cx][cy] + 1;
					q.push({nx, ny});
				}
		}
	}
}

int main(void) {
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		cin >> sx >> sy;
		cin >> ex >> ey;
		memset(m, 0, sizeof(m));
		bfs();
	}
	return 0;
}

