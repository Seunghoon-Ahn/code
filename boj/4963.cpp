#include <bits/stdc++.h>
using namespace std;
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int mmap[52][52];
bool visit[52][52];
int tmp1, tmp2;

void dfs(int x, int y) {
	visit[x][y] = true;
	for(int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if(0 <= nx && nx < tmp2 && 0 <= ny && ny < tmp1)
			if(!visit[nx][ny] && mmap[nx][ny] == 1)
				dfs(nx, ny);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	while(1) {
		int cnt = 0;
		memset(mmap, 0, sizeof(mmap));
		memset(visit, 0, sizeof(visit));
		cin >> tmp1 >> tmp2;
		if(tmp1 == 0 && tmp2 == 0) break;
		for(int i = 0; i < tmp2; i++)
			for(int j = 0; j < tmp1; j++)
				cin >> mmap[i][j];
		
		for(int i = 0; i < tmp2; i++)
			for(int j = 0; j < tmp1; j++)
				if(!visit[i][j] && mmap[i][j] == 1) {
					dfs(i, j);
					cnt++;
				}
		cout << cnt << '\n';
	}
	return 0;
}
