#include <bits/stdc++.h>
using namespace std;
int N, M;
int par[203];
vector <int> city;

void init(int N) {
	for(int i = 1; i <= N; i++)
		par[i] = i;
}

int find(int x) {
	if(par[x] == x)
		return x;
	return par[x] = find(par[x]);
}

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return;
	
	par[x] = y;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp;
	cin >> N >> M;
	init(N);
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			cin >> tmp;
			if(tmp)
				unite(i, j);
		}
	}
	for(int i = 1; i <= M; i++) {
		cin >> tmp;
		city.push_back(tmp);
	}
	int parent = find(city[0]);
	if(M == 1) {
		cout << "YES" << '\n';
		return 0;
	}
	for(int i = 1; i < M; i++) {
		if(parent != find(city[i])) {
			cout << "NO" << '\n';
			return 0;
		}
	}
	cout << "YES" << '\n';
	return 0;
}

