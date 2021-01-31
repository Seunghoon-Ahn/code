#include <bits/stdc++.h>
using namespace std;
vector <int> g[32005], st;
bool visit[32005];

void dfs(int n) {
	visit[n] = true;
	for(int next : g[n])
		if(!visit[next])
			dfs(next);
	st.push_back(n);
}

int main(void) {
	int M, N;
	cin >> N >> M;

	for(int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
	}

	for(int i = 1; i <= N; i++)
		if(!visit[i])
			dfs(i);
	
	reverse(st.begin(), st.end());

	for(int i = 0; i < st.size(); i++)
		cout << st[i] << ' ';

	return 0;
}

