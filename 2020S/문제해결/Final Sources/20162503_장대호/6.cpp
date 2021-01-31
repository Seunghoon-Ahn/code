#include<cstdio>
#include<iostream>

int map[100][100];
int visit[100][100];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1, 0,0 };
int N, M;
void dfs(int x, int y) {
	visit[x][y] = -1;
	for (int i = 0; i < 4; i++) {
		int nx = dx[i] + x;
		int ny = dy[i] + y;
		if ((nx>= 0) && (nx <N) && (ny >=0) && (ny < M)) {
			if (visit[nx][ny] == 0 && map[nx][ny] == 0)
				dfs(nx, ny);
		}
	}
}
int main(void) {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				visit[i][j] = -2;
		}
	}
	dfs(0, 0);
	
	int times = 0;
	int check = 1;
	while (check == 1) {
		check = 0;
		times++;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visit[i][j] == -2) {
				
					int count = 0;
					for (int k = 0; k < 4; k++) {
						int nx = dx[k] + i;
						int ny = dy[k] + j;
						if (visit[nx][ny] == -1 || (visit[nx][ny] > 0 && visit[nx][ny] < times)) {
							
							count++;
						}
					}
					if (count >= 2) {
						visit[i][j] = times;
						check = 1;
					}
					
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visit[i][j] == 0) {
					for (int k = 0; k < 4; k++) {
						int nx = dx[k] + i;
						int ny = dy[k] + j;
						if (visit[nx][ny] == -1 || (visit[nx][ny] > 0 && visit[nx][ny] <= times)) {
							visit[i][j] = times;
						}
					}
				}
			}
		}
	
	}
	printf("%d\n", times-1);
}