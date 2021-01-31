#include <bits/stdc++.h>
using namespace std;
int N, P;
vector <int> g[403];
int v[403][403];
int f[403][403];

int count_flow(void);

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> P;
	int tmp1, tmp2;
	for(int i = 0; i < P; i++) {
		cin >> tmp1 >> tmp2;
		g[tmp1].push_back(tmp2);
		g[tmp2].push_back(tmp1);
		v[tmp1][tmp2] = 1;
		v[tmp2][tmp1] = 1;
	}
	int res = count_flow();
	cout << res << '\n';
	return 0;
}

int count_flow(void) {
	queue<int> q;
	int total = 0;
	while(1) {
		int arr[403];
		bool visit[403];
		memset(visit, 0, sizeof(visit));
		memset(arr, 0, sizeof(arr));
		visit[1] = true;
		q.push(1);

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
		if(visit[2] == false)
			break;
		int mmax = 2100000000;
		for(int i = 2; i != 1; i = arr[i])
			mmax = min(mmax, v[arr[i]][i] - f[arr[i]][i]);
		for(int i = 2; i != 1; i = arr[i]) {
			f[arr[i]][i] += mmax;
			f[i][arr[i]] -= mmax;
		}
		total += mmax;
	}
	return total;
}
