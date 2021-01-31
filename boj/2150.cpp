#include <bits/stdc++.h>
using namespace std;

int V, E;
bool visit[10101];
vector <int> g[10101], rg[10101], st;
vector <vector<int>> scc;
int cnt = 0;

void dfs(int n) {
	visit[n] = true;
	for(int next : g[n]) {
		if(!visit[next])
			dfs(next);
	}
	st.push_back(n);
}

void dfs2(int n) {
	visit[n] = true;
	for(int next : rg[n]) {
		if(!visit[next])
			dfs2(next);
	}
	scc.back().push_back(n);
}

int main(void) {
	cin >> V >> E;
	for(int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		rg[b].push_back(a);
	}

	for(int i = 1; i <= V; i++) {
		if(!visit[i])
			dfs(i);
	}

	reverse(st.begin(), st.end());
	memset(visit, 0, sizeof(visit));

	for(int n : st) {
		if(!visit[n]) {
			scc.push_back(vector<int>());
			dfs2(n);
		}
	}

	cout << scc.size() << '\n';
	
	for(int i = 0; i < scc.size(); i++)
		sort(scc[i].begin(), scc[i].end());
	sort(scc.begin(), scc.end());

	for(int i = 0; i < scc.size(); i++) {
		for(int num : scc[i])
			cout << num << ' ';
		cout << "-1\n";
	}
	
	return 0;
}
