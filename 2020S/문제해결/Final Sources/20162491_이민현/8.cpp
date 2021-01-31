#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

bool check[101];
int match[101];
vector<int> vt[501];

bool dfs(int a) {
	
	if (check[a] == 0) {
		check[a] = true;
	}
	else {
		return false;
	}


	for (int b : vt[a]) {
		if (match[b] == 0) {
			match[b] = a;
			return true;
		}
	}
		
	for (int b : vt[a]) {
		if (dfs(match[b])) {
			match[b] = a;
			return true;
		}
	}
	
	return false;
}


int n, m;
int main(void) {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		vt[a].push_back(b);
	}
	
	int ans = 0;

	memset(match, 0, sizeof(match));
	
	for (int i = 1; i <= n; i++) {
		memset(check, 0, sizeof(check));
		if (dfs(i)) {
			ans++;
		}
	}

	cout << ans;

}