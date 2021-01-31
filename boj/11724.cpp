#include <bits/stdc++.h>
using namespace std;

vector <int> g[1002];
bool visit[1002];
int N, M;

void dfs(int n) {
	visit[n] = true;
	for(int next : g[n]) {
		if(visit[next] == false)
			dfs(next);
	}
}

int main(void) {
	int tmp1, tmp2;
	cin >> N >> M;
	for(int i = 0; i < M; i++) {
		cin >> tmp1 >> tmp2;
		g[tmp1].push_back(tmp2);
		g[tmp2].push_back(tmp1);
	}
	int cnt = 0;
	for(int i = 1; i <= N; i++) {
		if(visit[i] == false) {
			dfs(i);
			cnt++;
		}
	}
	cout << cnt << '\n';
	return 0;
}
