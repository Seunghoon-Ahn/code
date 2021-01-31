#include <bits/stdc++.h>
using namespace std;
int g[102][102];
bool visit[102][102];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int n, res = 0;
int maxD = 0;

void dfs(int a, int b, int h) {
	visit[a][b] = true;
	for(int i = 0; i < 4; i++) {
		int nx = a + dx[i];
		int ny = b + dy[i];
		if(0 < nx && nx <= n && 0 < ny && ny <= n)
			if(g[nx][ny] > h && !visit[nx][ny])
				dfs(nx, ny, h);
	}
}

int main(void) {
	cin >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			cin >> g[i][j];
			maxD = max(maxD, g[i][j]);
		}
	for(int h = 0; h <= maxD; h++) {
		memset(visit, 0, sizeof(visit));
		int safe = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(g[i][j] > h && !visit[i][j]) {
					dfs(i, j, h);
					safe++;
				}
			}
		}
		res = max(res, safe);
	}
	cout << res << '\n';
	return 0;
}

		
	

