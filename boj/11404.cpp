#include <bits/stdc++.h>
using namespace std;
const int MN = 101;
const int INF = 1e9;
int d[MN][MN];
int N, M;
int main(void) {
	cin >> N >> M;
	fill(&d[0][0], &d[MN-1][MN], INF);
	for(int i = 1; i <= N; i++)
		d[i][i] = 0;
	for(int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		d[u][v] = min(d[u][v], w);
	}
	for(int k = 1; k <= N; k++) {
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			if(d[i][j] == INF)
				cout << "0 ";
			else
				cout << d[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}

