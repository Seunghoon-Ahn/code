#include <bits/stdc++.h>
using namespace std;
int R, C, N;
const int MN = 603;
vector <int> g[MN];
int v[MN][MN];
int f[MN][MN];
bool check[MN][MN];

int count_flow(void);

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> N;
	int tmp1, tmp2;
	for(int i = 1; i <= N; i++) {
		cin >> tmp1 >> tmp2;
		check[tmp1][tmp2] = true;
	}
	for(int i = 1; i <= R; i++) {
		g[0].push_back(i);
		g[i].push_back(0);
		v[0][i] = 1;
		for(int j = 1; j <= C; j++) {
			if(!check[i][j]) {
				g[i].push_back(j+300);
				g[j+300].push_back(i);
				v[i][j + 300] = 1;
			}
		}
	}
	for(int j = 1; j <= C; j++) {
		g[j + 300].push_back(601);
		g[601].push_back(j+300);
		v[j + 300][601] = 1;
	}
	int res = count_flow();
	cout << res <<'\n';
	return 0;
}
	
int count_flow(void) {
	queue <int> q;
	int total = 0;
	while(1) {
		int arr[603];
		bool visit[603];
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
		if(visit[601] == false)
			break;
		int mmax = 2100000000;
		for(int i = 601; i != 0; i = arr[i])
			mmax = min(mmax, v[arr[i]][i] - f[arr[i]][i]);
		for(int i = 601; i != 0; i = arr[i]) {
			f[arr[i]][i] += mmax;
			f[i][arr[i]] -= mmax;
		}
		total += mmax;
	}
	return total;
}
			
