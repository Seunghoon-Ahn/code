// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;

int n, m;
int map[102][102];
vector < pair<int, int> > v;

int di[4] = { -1,0,1,0 };
int dj[4] = { 0,1,0,-1 };

void bfs() {
	queue<pair<int, int>> q;
	map[0][0] = -1;
	q.push({ 0, 0 });

	while (!q.empty()) {
		auto t = q.front();
		q.pop();
		int ti = t.first;
		int tj = t.second;

		for (int k = 0; k < 4; k++) {
			int ni = ti + di[k];
			int nj = tj + dj[k];

			if (ni < 0 || nj < 0 || ni >= n || nj >= m || map[ni][nj] != 0) continue;

			q.push({ ni,nj });
			map[ni][nj] = -1;
		}
	}
}

int main() {
	int res = 0;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				v.push_back({ i,j });
			}
		}
	}

	

	while (1) {
		bool all = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != 0) {
					all = false;
					break;
				}
			}
			if (!all) break;
		}
		if (all) break;
		res++;
		bfs();

		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == -1)cout << "* ";
				else	cout << map[i][j] << ' ';
			}
			cout << '\n';
		}
*/
		for (auto t : v) {
			int ti = t.first;
			int tj = t.second;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int ni = ti + di[k];
				int nj = tj + dj[k];
				if (map[ni][nj] == -1) cnt++;
			}

			if (cnt>=2) {
				map[ti][tj] = 2;
			}
		}
		v.clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 2 || map[i][j] == -1) map[i][j] = 0;
				else {
					v.push_back({ i,j });
				}
			}
		}
	}
	cout << res;

	return 0;
}