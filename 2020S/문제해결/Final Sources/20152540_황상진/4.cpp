// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "vector"
#include "queue"
#include "stack"
#include "algorithm"

using namespace std;

int map[302][302];

int n, m, k;

int v[302];

void dfs() {
	stack<pair<int, int>>s;
	s.push({ 1,0 });
	v[1] = 0;

	while (!s.empty()) {
		auto t = s.top();
		s.pop();
		int tt = t.first;
		int tsati = t.second;

		for (int k = tt + 1; k <= n; k++) {
			if (map[tt][k] == 0) continue;
			int temp = tsati + map[tt][k];

			if (v[k] == 0 || v[k] < temp) {
				v[k] = temp;
				s.push({ k,temp });
			}
		}
	}
}

int main() {

	cin >> n >> m >> k;
	memset(map, -1, sizeof(map));
	int s, l, deli;
	for(int i=0;i<k;i++){
		cin >> s >> l >> deli;
		if (s > l || map[s][l] > deli) continue;
		map[s][l] = deli;
	}

	/*for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}*/

	dfs();

	cout << v[n];

	return 0;
}