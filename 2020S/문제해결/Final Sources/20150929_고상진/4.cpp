#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

int N, M, K, u, v, w, m;
int flight[301][301];
int answer;
vector<vector<pii>> edge;

int main() {
	cin >> N >> M >> K;
	
	edge.resize(N + 1);

	for (int i = 0; i < K; i++) {
		cin >> u >> v >> w;
		if (u < v) edge[u].push_back({ v, w });
	}

	priority_queue<pii> p_queue;
	p_queue.push({ 1, 1001 });
	pii cur;
	while (!p_queue.empty()) {
		cur = p_queue.top();
		p_queue.pop();
		v = cur.second / 1000;
		m = cur.second % 1000;
		
		if (flight[v][m] < cur.first) {
			//cout << v << " " << m << " " << cur.first << endl;
			flight[v][m] = cur.first;

			if (v == N) {
				answer = max(answer, cur.first);
			}

			if (m < M) {
				for (int i = 0; i < edge[v].size(); i++) {
					p_queue.push({ cur.first + edge[v][i].second, 1000 * edge[v][i].first + m + 1 });
				}
			}
		}
	}
	cout << (answer - 1);
}
