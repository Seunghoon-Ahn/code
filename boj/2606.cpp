#include <bits/stdc++.h>
using namespace std;
vector <int> v[102];
bool visit[102];
int pc, n;
int cnt = 0;

void dfs(int num) {
	visit[num] = true;
	for(int next : v[num]) {
		if(!visit[next]) {
			visit[next] = true;
			dfs(next);
			cnt++;
		}
	}
}

int main(void) {
	int tmp1, tmp2;
	cin >> pc;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> tmp1 >> tmp2;
		v[tmp1].push_back(tmp2);
		v[tmp2].push_back(tmp1);
	}

	dfs(1);
	cout << cnt;
	return 0;
}
