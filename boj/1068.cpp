#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int D;
int r;
int leaf = 0;
vector <int> g[52];

void search(int n) {
	if(n == D) 
		return;
	if(g[n].size() == 0) {
		leaf++;
		return;
	}
	if(g[n].size() == 1 && g[n][0] == D) {
		leaf++;
		return;
	}
	for(int next : g[n])
		search(next);
	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp;
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> tmp;
		if(tmp == -1) {
			r = i;
			continue;
		}
		g[tmp].push_back(i);
	}
	cin >> D;
	if(D == r) {
		cout << 0 << '\n';
		return 0;
	}
	if(N == 2)  {
		cout << 1 << '\n';
		return 0;
	}
	search(r); //루트부터 탐색해서 리프노드 갯수 세기
	cout << leaf << '\n';
	return 0;
}

