#include <bits/stdc++.h>
using namespace std;
int T;
int M, N, K;
int mmap[52][52];
bool visit[52][52];
vector <int> res;
int cnt = 0;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void dfs(int x, int y) {
	visit[x][y] = true;

	for(int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];

		if(0 <= nx && nx < N && 0 <= ny && ny < M) {
			if(!visit[nx][ny] && mmap[nx][ny] == 1) {
				dfs(nx, ny);
			}
		}
	}
}

int main(void) {
	cin >> T;
	for(int t = 0; t < T; t++) {
		memset(mmap, 0, sizeof(mmap));
		memset(visit, 0, sizeof(visit));
		cin >> M >> N >> K;
		for(int i = 0; i < K; i++) {
			int tmp1, tmp2;
			cin >> tmp1 >> tmp2;
			mmap[tmp2][tmp1] = 1;
		}
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if(!visit[i][j] && mmap[i][j] == 1) {
					dfs(i, j);
					cnt++;
				}
			}
		}
		res.push_back(cnt);
		cnt = 0;
	}
	for(int i = 0; i < T; i++)
		cout << res[i] << '\n';
	return 0;
}

