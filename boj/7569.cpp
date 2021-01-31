#include <bits/stdc++.h>
using namespace std;
typedef struct {
	int x;
	int y;
	int z;
}tomato;
queue <tomato> q;
int box[102][102][102];
int dx[6] = {-1, 0, 0, 1, 0, 0};
int dy[6] = {0, -1, 1, 0, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};
int M, N, H;

void bfs(void) {
	while(!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cz = q.front().z;
		q.pop();
		for(int i = 0; i < 6; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int nz = cz + dz[i];
			if(0 <= nx && nx < N && 0 <= ny && ny < M && 0 <= nz && nz < H) {
				if(!box[nx][ny][nz]) {
					box[nx][ny][nz] = box[cx][cy][cz] + 1;
					tomato tmp;
					tmp.x = nx;
					tmp.y = ny;
					tmp.z = nz;
					q.push(tmp);
				}
			}
		}
	}
}

int main(void) {
	cin >> M >> N >> H;
	for(int k = 0; k < H; k++) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				cin >> box[i][j][k];
				if(box[i][j][k] == 1) {
					tomato tmp;
					tmp.x = i;
					tmp.y = j;
					tmp.z = k;
					q.push(tmp);
				}
			}
		}
	}

	bfs();
	int day = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			for(int k = 0; k < H; k++) {
				if(box[i][j][k] == 0) {
					cout << -1 << '\n';
					return 0;
				}
				if(day < box[i][j][k])
					day = box[i][j][k];
			}
		}
	}
	cout << day - 1 << '\n';
	return 0;
}

