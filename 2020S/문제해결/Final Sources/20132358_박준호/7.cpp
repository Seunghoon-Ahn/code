#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int N, M;

typedef pair<int, pair<int, int>> BUS;

#define COST .first
#define START .second.first
#define END .second.second

int get_root(vector<int>& parent, int node) {
	if (node == parent[node]) {
		return node;
	}
	else {
		return get_root(parent, parent[node]);
	}
}

int main(void) {
	//freopen("./ex.txt", "r", stdin);
	//freopen("./out.txt", "w+", stdout);

	int N, M;

	scanf("%d %d", &N, &M);

	vector<vector<int>> edge(N);
	priority_queue<BUS> busQ;

	vector<int> parent(N);

	for (int i = 0; i < N; i++) {
		parent[i] = i;
	}

	for (int m = 0; m < M; m++) {
		int s, e, c;

		scanf("%d %d %d", &s, &e, &c);

		busQ.push(make_pair(c, make_pair(s, e)));
	}

	int cnt = 0;

	while (cnt < N - 1) {

	}


	return 0;
}