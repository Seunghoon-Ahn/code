#include <bits/stdc++.h>
using namespace std;
int n, st, en, m;
int chon[103][103];
int res[103];
queue <int> q;

int main(void) {
	int tmp1, tmp2;
	cin >> n;
	cin >> st >> en;
	cin >> m;
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2;
		chon[tmp1][tmp2] = 1;
		chon[tmp2][tmp1] = 1;
	}
	q.push(st);
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(int i = 1; i <= n; i++) {
			if(!chon[cur][i] || res[i])
				continue;
			res[i] = res[cur] + 1;
			q.push(i);
		}
	}
	if(res[en] == 0)
		cout << -1;
	else
		cout << res[en];

	return 0;
}
