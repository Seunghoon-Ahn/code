#include <bits/stdc++.h>
using namespace std;
const int MN = 1001;
int t[MN];
vector<int> g[MN], st;
bool visited[MN];
int fin[MN];

void dfs(int n) {
	visited[n] = true;
	for(int next : g[n])
		if(!visited[next])
			dfs(next);

	st.push_back(n);
}

int main(void) {
	int T;
	cin >> T;
	while(T--) {

		int N, K, W;
		cin >> N >> K;
		for(int i = 1; i <= N; i++)
			cin >> t[i];
		for(int i = 0; i < K; i++) {
			int a, b;
			cin >> a >> b;
			g[a].push_back(b);
		}
		cin >> W;
		
		for(int i = 1; i <= N; i++) {
			if(!visited[i])
				dfs(i);
		}
		reverse(st.begin(), st.end());

		for(int n : st) {
			fin[n] += t[n];
			for(int next : g[n])
				fin[next] = max(fin[next], fin[n]);
		}

		cout << fin[W] << '\n';
		
		memset(t, 0, sizeof(t));
		memset(fin, 0, sizeof(fin));
		st.clear();
		for(int i = 0; i <= N; i++)
			g[i].clear();
		memset(visited, 0, sizeof(visited));
	}
	return 0;
}
