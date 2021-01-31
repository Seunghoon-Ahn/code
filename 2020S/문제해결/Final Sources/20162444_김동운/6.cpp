#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int MN = 101;

struct ch {
	int i, j;
};
queue<ch> q;
int arr[MN][MN];
int di[4] = { 1, -1, 0, 0 };
int dj[4] = { 0, 0, 1, -1 };
vector<ch> del;
bool visit[MN][MN];
int N, M;
bool dfs(int x, int y)
{
	visit[x][y] = true;
	for (int d = 0; d < 4; d++) {
		int ni = x + di[d];
		int nj = y + dj[d];
		if (!(0 <= ni && ni < N && 0 <= nj && nj < M)) continue;
		if (visit[ni][nj] == false && arr[ni][nj] != 1) {
			visit[ni][nj] = true;
			if (ni == 0 || ni == N - 1 || nj == 0 || nj == M)
				return true;
			if (dfs(ni, nj))
				return true;
		}
	}
	return false;
}
void dfs2(int x, int y)
{
	visit[x][y] = true;
	arr[x][y] = 0;
	for (int d = 0; d < 4; d++) {
		int ni = x + di[d];
		int nj = y + dj[d];
		if (!(0 <= ni && ni < N && 0 <= nj && nj < M)) continue;
		if (visit[ni][nj] == false && arr[ni][nj] == 2) {
			visit[ni][nj] = true;
			dfs2(ni, nj);
		}
	}
}
int main(void)
{
	ios::sync_with_stdio(false);	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1)
				q.push({i,j});			
		}
	}	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == 1) {
				for (int d = 0; d < 4; d++) {
					int ni = i + di[d];
					int nj = j + dj[d];
					if (arr[ni][nj] == 0) {
						memset(visit, 0, sizeof(visit));
						if (dfs(ni, nj) == false)
							arr[ni][nj] = 2;
					}
				}
			}
		}
	}

	int res = 0;
	for (int n = 0; n < 200; n++) {
		for (int i = 1; i < N - 1; i++) {
			for (int j = 1; j < M - 1; j++) {
				int cnt = 0;
				if (arr[i][j] != 1) continue;
				for (int d = 0; d < 4; d++) {
					int ni = i + di[d];
					int nj = j + dj[d];
					if (arr[ni][nj] == 0)
						cnt++;
				}
				if (cnt > 1)
					del.push_back({ i, j });
			}
		}
		if (del.size() == 0)
			break;
		else
			res++;
		for (auto dele : del) {
			arr[dele.i][dele.j] = 0;
			for (int d = 0; d < 4; d++) {
				int ni = dele.i + di[d];
				int nj = dele.j + dj[d];
				if (arr[ni][nj] == 2) {
					memset(visit, 0, sizeof(visit));
					dfs2(ni, nj);
				}
			}
		}
		del.clear();		
	}

	cout << res;
}