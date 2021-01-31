#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

int N, M, a, b, c, from, to, answer;
bool visited[1001];
vector<vector<pii>> edge;

int main() {
	cin >> N >> M;

	edge.resize(N + 1);
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		edge[a].push_back({ b, c });
	}
	cin >> from >> to;

	priority_queue<pii> p_queue;
	p_queue.push({ 0, from });
	pii cur;
	while (!p_queue.empty()) {
		cur = p_queue.top();
		p_queue.pop();
		if (!visited[cur.second]) {
			if (cur.second == to) {
				answer = -cur.first;
				break;
			}
			visited[cur.second] = true;
			for (int i = 0; i < edge[cur.second].size(); i++) {
				p_queue.push({ cur.first - edge[cur.second][i].second, edge[cur.second][i].first });
			}
		}
	}

	cout << answer;
}