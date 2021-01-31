#include <stdio.h>
#include <vector>
#include <queue>
#define N 100

using namespace std;
typedef pair<int, int> pi;
int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };
int n, m, cnt = 0, time = 0;
int a[N + 5][N + 5];
int visit[N + 5][N + 5];
queue<pi> q;

void melt();
pi findS();
int main() {

	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 1)
				cnt++;
		}
	}
	while (cnt > 0) {
		pi start = findS();
		for (int i = 1; i <= n; i++) {
			fill_n(visit[i], m, 0);
		}
		q.push(start);
		visit[start.first][start.second] = -1;
		while (!q.empty()) {
			pi now = q.front();
			q.pop();
			for (int i = 0; i < 4; i++) {
				int nr = now.first + dr[i];
				int nc = now.second + dc[i];
				if (nr <1 || nr > n)
					continue;
				if (nc <1 || nc > m)
					continue;
				if (a[nr][nc] == 1) {
					visit[nr][nc] ++;
					continue;
				}
				if (a[nr][nc] == 0 && visit[nr][nc] == 0) {
					q.push({ nr,nc });
					visit[nr][nc] = -1;
				}
			}
		}
		melt();
		time++;
	}
	printf("%d", time);
	
}
void melt() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (visit[i][j] >= 2) {
				a[i][j] = 0;
				cnt--;
			}
		}
	}
}
pi findS() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 0) {
				return{ i,j };
			}
		}
	}
	return{ -1,-1 };
}