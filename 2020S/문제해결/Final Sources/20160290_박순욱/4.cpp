#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, K;
vector<vector<pair<int, int>>> town;

int solve(int, int);

int main() {
	scanf("%d %d %d", &N, &M, &K);
	town.resize(N + 1);
	for (int i = 0; i < K; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(a < b)
			town[a].push_back(make_pair(b, c));
	}

	printf("%d\n", solve(1, N));

	return 0;
}

int solve(int from, int to) {

	priority_queue<pair<pair<int, int>, int>> pq;
	pq.push(make_pair(make_pair(0, from), 1));
	int totalTime[1001];
	totalTime[from] = 0;

	while (!pq.empty()) {
		int curr = pq.top().first.second;
		int time = pq.top().first.first;
		int travel = pq.top().second;
		pq.pop();
		if (travel >= M)
			continue;
		travel++;
		for (int i = 0; i < town[curr].size(); i++) {
			int next = town[curr][i].first;
			int nextTime = town[curr][i].second;
			totalTime[next] = max(time + nextTime, totalTime[next]);
			pq.push(make_pair(make_pair(time + nextTime, next), travel));
		}
	}
	return totalTime[to];
}