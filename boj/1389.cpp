#include <bits/stdc++.h>
using namespace std;
int n, m;
int f[103][103];
bool visit[103][103];
queue <int> q;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp1, tmp2;
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2;
		f[tmp1][tmp2] = 1;
		f[tmp2][tmp1] = 1;
	}

	int mmin = 2000000000;
	int res = 0;
	for(int i = 1; i <= n; i++) {
		q.push(i);
		visit[i][i] = true;
		int sum = 0;
		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int j = 1; j <= n; j++) {
				if(!visit[i][j] && f[cur][j] == 1) {
					q.push(j);
					f[i][j] = f[i][cur] + f[cur][j];
					visit[i][j] = true;
					sum += f[i][j];
				}
			}
		}

		if(sum < mmin) {
			mmin = sum;
			res = i;
		}
	}
	cout << res << '\n';
	return 0;
}

