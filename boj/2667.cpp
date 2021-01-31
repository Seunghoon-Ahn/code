#include <bits/stdc++.h>
using namespace std;
int mmap[27][27];
bool visit[27][27];
int w, cnt = 0;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

vector <int> res;
int hcnt = 1;
void dfs(int x, int y) {
	visit[x][y] = true;
	for(int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		
		if(0 <= nx && nx < w && 0 <= ny && ny < w)
			if(!visit[nx][ny] && mmap[nx][ny] == 1) {
				dfs(nx, ny);
				hcnt++;
			}
	}
	return;
}

int main(void) {
	cin >> w;
	for(int i = 0; i < w; i++)
		for(int j = 0; j < w; j++)
			scanf("%1d", &mmap[i][j]);

	for(int i = 0; i < w; i++)
		for(int j = 0; j < w; j++)
			if(!visit[i][j] && mmap[i][j] == 1) {
				dfs(i, j);
				cnt++;
				res.push_back(hcnt);
				hcnt = 1;
			}
	cout << cnt << '\n';
	sort(res.begin(), res.end());
	for(int i = 0; i < res.size(); i++)
		cout << res[i] << '\n';
	return 0;
}

