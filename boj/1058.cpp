#include <bits/stdc++.h>
using namespace std;
int n, maxf = 0;
char tmp;
vector <int> f[52];
vector <int> res;
bool visit[52];
int main(void) {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%c", &tmp);
			if(tmp == 'Y') {
				f[i].push_back(j);
			}
		}
		scanf("%c", &tmp);
	}
	queue<int> q;

	for(int i = 1; i <= n; i++) {
		int cnt = 0;
		visit[i] = true;
		for(int next : f[i]) {
			if(!visit[next]) {
				q.push(next);
				visit[next] = true;
				cnt++;
			}
		}

		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int next : f[cur]) {
				if(!visit[next]) {
					visit[next] = true;
					cnt++;
				}
			}
		}
		res.push_back(cnt);
		memset(visit, 0, sizeof(visit));
	}
	sort(res.begin(), res.end());
	cout << res[res.size() - 1];
	return 0;
}

