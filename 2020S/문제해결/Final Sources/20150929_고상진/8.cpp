#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int v;
	bool res;
	int rev;
};

int N, M, a, b, cur, answer;
vector<vector<Edge>> edge;
int LEV[202];
int start[202];

bool BFS() {
	for (int i = 1; i < N * 2 + 2; i++) {
		LEV[i] = 0;
	}
	LEV[0] = 1;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		for (int i = 0; i < edge[cur].size(); i++) {
			if (LEV[edge[cur][i].v] == 0 && edge[cur][i].res) {
				LEV[edge[cur][i].v] = LEV[cur] + 1;
				q.push(edge[cur][i].v);
			}
		}
	}

	return LEV[N * 2 + 1] > 0 ? true : false;
}

bool sendFlow(int v) {
	if (v == N * 2 + 1) return true;

	for (; start[v] < edge[v].size(); start[v]++) {
		if (edge[v][start[v]].res && LEV[edge[v][start[v]].v] == LEV[v] + 1) {
			if (sendFlow(edge[v][start[v]].v)) {
				edge[v][start[v]].res = false;
				edge[edge[v][start[v]].v][edge[v][start[v]].rev].res = true;
				return true;
			}
		}
	}
	return false;
}

int main() {
	cin >> N >> M;
	edge.resize(N * 2 + 2);
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		Edge x = { N + b, true, edge[N + b].size() };
		Edge y = { a, false, edge[a].size() };
		edge[a].push_back(x);
		edge[N + b].push_back(y);
	}
	for (int i = 1; i <= N; i++) {
		Edge x = { i, true, edge[i].size() };
		Edge y = { 0, false, edge[0].size() };
		edge[0].push_back(x);
		edge[i].push_back(y);
		Edge z = { N * 2 + 1, true, edge[N * 2 + 1].size() };
		Edge w = { N + i, false, edge[N + i].size() };
		edge[N + i].push_back(z);
		edge[N * 2 + 1].push_back(w);
	}
	
	while (BFS()) {
		for (int i = 0; i < N * 2 + 2; i++) {
			start[i] = 0;
		}
		while (sendFlow(0)) answer++;
	}
	cout << answer;
}