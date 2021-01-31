#include <bits/stdc++.h>
using namespace std;
bool visit[504];
int t[504];
int fin[504];
vector <int> g[504], st;

void dfs(int n) {
	visit[n] = true;
	for(int next : g[n])
		if(!visit[next])
			dfs(next);

	st.push_back(n);
}

int main(void) {
	int N;
	cin >> N;
	for(int i = 1; i <= N; i++) {
		cin >> t[i];
		while(1) {
			int tmp;
			cin >> tmp;
			if(tmp == -1)
				break;
			g[tmp].push_back(i);
		}
	}

	for(int i = 1; i <= N; i++)
		if(!visit[i])
			dfs(i);
	
	reverse(st.begin(), st.end());

	for(int n : st) {
		fin[n] += t[n];
		for(int next : g[n])
			fin[next] = max(fin[next], fin[n]);
	}

	for(int i = 1; i <= N; i++)
		cout << fin[i] << '\n';
	
	return 0;
}

