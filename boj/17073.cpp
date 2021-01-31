#include <bits/stdc++.h>
using namespace std;
int N, W;
vector <int> t[500002];
bool visit[500002];
int res = 0;
void bfs(void) {
	visit[1] = true;
	queue<int> q;
	q.push(1);
	while(!q.empty()) {
		bool nonleaf = false;
		int cur = q.front();
		q.pop();
		for(int next : t[cur]) {
			if(visit[next] == 0) {
				visit[next] = true;
				nonleaf = true;
				q.push(next);
			}
		}
		if(!nonleaf)
			res++;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> W;
	int tmp1, tmp2;
	for(int i = 0; i < N - 1; i++) {
		cin >> tmp1 >> tmp2;
		t[tmp1].push_back(tmp2);
		t[tmp2].push_back(tmp1);
	}
	bfs();
	printf("%lf\n", (double)W / (double)res);
	return 0;
}


