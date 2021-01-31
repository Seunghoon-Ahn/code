#include <bits/stdc++.h>
using namespace std;
vector <int> t[500002];
int visit[500002];
int N;
long long res = 0;

void bfs(void) {
	visit[1] = 1;
	queue<int> q;
	q.push(1);
	while(!q.empty()) {
		bool nonleaf = false;
		int cur = q.front();
		q.pop();
		for(int next : t[cur]) {
			if(visit[next] == 0) {
				visit[next] = visit[cur] + 1;
				nonleaf = true;
				q.push(next);
			}
		}
		if(!nonleaf)
			res += visit[cur] - 1;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int tmp1, tmp2;
	for(int i = 0; i < N - 1; i++) {
		cin >> tmp1 >> tmp2;
		t[tmp1].push_back(tmp2);
		t[tmp2].push_back(tmp1);
	}
	bfs();
	if(res % 2)
		cout << "Yes" << '\n';
	else
		cout << "No" << '\n';
	return 0;
}
	

