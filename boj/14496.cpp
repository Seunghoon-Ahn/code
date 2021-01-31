#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int>> pp;
int a, b;
int N, M;
vector <int> letter[1003];
//int depth = -1;
bool visit[1003];

void bfs(int num) {
	priority_queue <pp, vector<pp>, greater<pp>> pq;
	for(int next : letter[num])
		pq.push({1, {num, next}});
	visit[num] = true;

	while(!pq.empty()) {
		pp tmp = pq.top();
		pq.pop();
		if(tmp.second.second == b) {
			cout << tmp.first;
			exit(0);
		}
		for(int next : letter[tmp.second.second]) {
			if(!visit[next]) {
				pq.push({tmp.first + 1, {tmp.second.second, next}});
				visit[next] = true;
			}
		}
	}
}

int main(void) {
	cin >> a >> b;
	cin >> N >> M;
	int tmp1, tmp2;
	for(int i = 0; i < M; i++) {
		cin >> tmp1 >> tmp2;
		letter[tmp1].push_back(tmp2);
		letter[tmp2].push_back(tmp1);
	}
	if(a == b) {
		cout << 0 << '\n';
		return 0;
	}
	bfs(a);
	cout << -1 << '\n';
	return 0;
}


