#include <bits/stdc++.h>
using namespace std;
vector <int> f[502];
queue <int> q;
bool visit[502];
int n, m;
int tmp1, tmp2;
int cnt = 0;
int main(void) {
	cin >> n;
	cin >> m;
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2;
		f[tmp1].push_back(tmp2);
		f[tmp2].push_back(tmp1);
	}

	visit[1] = true;
	for(int next : f[1]) {
		q.push(next);
		visit[next] = true;
		cnt++;
	}
	
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(int i = 0; i < f[cur].size(); i++) {
			if(!visit[f[cur][i]]) {
				cnt++;
				visit[f[cur][i]] = true;
			}
		}
	}

	cout << cnt;
	return 0;
}


