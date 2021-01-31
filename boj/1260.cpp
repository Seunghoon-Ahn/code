#include <bits/stdc++.h>
using namespace std;
queue <int> q;
vector <int> ve[1002];
bool check[1002];
int n, m, v;

void dfs(int num) {
	check[num] = true;
	cout << num << ' ';
	for(int i = 0; i < ve[num].size(); i++) {
		int next = ve[num][i];
		if(!check[next])
			dfs(next);
	}
}

void bfs(int num) {
	q.push(num);
	check[num] = 1;
	while(!q.empty()) {
	 	num = q.front();
		q.pop();
		cout << num << ' ';
		for(int i = 0; i < ve[num].size(); i++) {
			int next = ve[num][i];
			if(!check[next]) {
				q.push(next);
				check[next] = 1;
			}
		}
	}
}

int main(void) {
	cin >> n >> m >> v;
	int tmp1, tmp2;
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2;
		ve[tmp1].push_back(tmp2);
		ve[tmp2].push_back(tmp1);
	}
	for(int i = 1; i <= n; i++)
		sort(ve[i].begin(), ve[i].end());
	dfs(v);
	cout << '\n';
	memset(check, 0, sizeof(check));
	bfs(v);
	return 0;
}
		
