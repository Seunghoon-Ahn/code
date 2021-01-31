#include <bits/stdc++.h>
using namespace std;
int n, m;
int d[20002];
int loc;
int far = -1, cnt = 0;
vector <int> v[20002];

void search(int st) {
	queue<int> q;
	q.push(st);
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(int i = 0; i < v[cur].size(); i++) {
			if(!d[v[cur][i]]) {
				d[v[cur][i]] = d[cur] + 1;
				q.push(v[cur][i]);
			}
		}
	}
}

int main(void) {
	int tmp1, tmp2;
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		cin >> tmp1 >> tmp2;
		v[tmp1].push_back(tmp2);
		v[tmp2].push_back(tmp1);
	}
	search(1);
	for(int i = 2; i <= n; i++) {
		if(d[i] > far) {
			far = d[i];
			loc = i;
		}
	}

	for(int i = 2; i <= n; i++)
		if(d[i] == far)
			cnt++;
	cout << loc << ' ' << far << ' ' << cnt << '\n';
	return 0;
}

