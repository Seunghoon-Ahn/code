// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;

int n, m, s, l;

int map[1002][1002];
int dp[1002];

void bfs() {
	queue<pair<int,int>> q;
	q.push({ s,0 });
	dp[s] = 0;

	while (!q.empty()) {
		auto t = q.front();
		int tp = t.first;
		int tcost = t.second;
		q.pop();

		for (int k = 1; k <= n; k++) {
			if (map[tp][k] != -1) {
				int temp = tcost + map[tp][k];
				if (dp[k] == -1 || dp[k] > temp) {
					dp[k] = temp;
					q.push({ k,temp });
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;
	memset(map, -1, sizeof(map));
	memset(dp, -1, sizeof(dp));
	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (map[a][b]!=-1 && map[a][b] < c) continue;
		map[a][b] = c;
	}

	cin >> s >> l;

	//for (int i = 1; i <= n; i++) {
	//	for (int j = 1; j <= n; j++) {
	//		cout << map[i][j] << ' ';
	//	}
	//	cout << '\n';
	//}

	bfs();

	cout << dp[l];

	return 0;
}