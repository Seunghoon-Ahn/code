#include <bits/stdc++.h>
using namespace std;
const int MN = 403;
int N, M;
vector <int> g[MN];
int v[MN][MN];
int f[MN][MN];

int count_flow(void);

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	int tmp1, tmp2;
	for(int i = 1; i <= N; i++) {
		g[0].push_back(i);
		g[i].push_back(0);
		v[0][i] = 1;
		cin >> tmp1;
		for(int j = 0; j < tmp1; j++) {
			cin >> tmp2;
			g[i].push_back(tmp2 + 200);
			g[tmp2 + 200].push_back(i);
			v[i][tmp2 + 200] = 1;
		}
	}
	for(int i = 1; i <= M; i++) {
		g[i + 200].push_back(401);
		g[401].push_back(i+200);
		v[i+200][401] = 1;
	}

	int res = count_flow();
	cout << res << '\n';
	return 0;
}

int count_flow(void) {
	queue <int> q;
	int total = 0;
	while(1) {
		int arr[403];
		bool visit[403];
		memset(visit, 0, sizeof(visit));
		memset(arr, 0, sizeof(arr));
		visit[0] = true;
		q.push(0);

		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int next : g[cur]) {
				if(!visit[next] && v[cur][next] - f[cur][next] > 0) {
					visit[next] = true;
					arr[next] = cur;
					q.push(next);
				}
			}
		}
		if(visit[401] == false)
			break;
		int mmax = 2100000000;
		for(int i = 401; i != 0; i = arr[i])
			mmax = min(mmax, v[arr[i]][i] - f[arr[i]][i]);
		for(int i = 401; i != 0; i = arr[i]) {
			f[arr[i]][i] += mmax;
			f[i][arr[i]] -= mmax;
		}
		total += mmax;
	}
	return total;
}
