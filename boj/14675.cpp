#include <bits/stdc++.h>
using namespace std;
int N;
vector <int> t[100002];
vector <pair<int, int>> input;
bool visit[100002];
bool leaf[100002];

void bfs(void) {
	queue<int> q;
	visit[1] = true;
	q.push(1);
	if(t[1].size() == 1)
		leaf[1] = true;

	while(!q.empty()) {
		bool nonleaf = false;
		int cur = q.front();
		q.pop();
		for(int next : t[cur]) {
			if(visit[next] == false) {
				visit[next] = true;
				nonleaf = true;
				q.push(next);
			}
		}
		if(!nonleaf)
			leaf[cur] = true;
	}
}



int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int tmp1, tmp2;
	for(int i = 0; i < N - 1; i++) {
		cin >> tmp1 >> tmp2;
		t[tmp1].push_back(tmp2);
		t[tmp2].push_back(tmp1);
	}
	bfs();
	int qnum;
	cin >> qnum;
	for(int i = 0; i < qnum; i++) {
		cin >> tmp1 >> tmp2;
		if(tmp1 == 1) {
			if(leaf[tmp2] == true)
				cout << "no\n";
			else
				cout << "yes\n";
		}
		else if(tmp1 == 2)
			cout << "yes\n";
	}
	return 0;
}

