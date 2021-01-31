#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <vector>
#pragma warning(disable:4996)

using namespace std;

int findAnswer();
bool DFS(int i);

vector<int> up_edge[101];
vector<int> down_edge[101];
bool visit[101];
int match[101];
int N, M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		up_edge[a].push_back(b);//위에서 아래로 edge
		down_edge[b].push_back(a);//아래서 위로 edge
	}

	printf("%d\n", findAnswer());

	return 0;
}

int findAnswer() {
	int cnt = 0;
	memset(match, -1, sizeof(match));
	for (int i = 1; i <= N; i++) {
		//printf("i=%d\n\n", i);
		memset(visit, false, sizeof(visit));
		if (DFS(i)) cnt++;
	}
	//for (int i = 1; i <= N; i++) {
	//	printf("match[%d]=%d\n", i, match[i]);
	//}
	return cnt;
}

bool DFS(int i) {
	visit[i] = true;
	//printf("start i=%d\n", i);
	for (int p = 0; p < up_edge[i].size(); p++) {
		int to = up_edge[i][p];
		//printf("to=%d\n", to);
		//if (visit[to]) continue;
		if (match[to] == -1) {
			match[to] = i;
			return true;
		}
	}
	for (int p = 0; p < up_edge[i].size(); p++) {
		int to = up_edge[i][p];//to라는 놈은 이미 match가 된 상태
		int to_up;
		for (int q = 0; q < down_edge[to].size(); q++) {
			if (match[to] == down_edge[to][q]) {
				to_up = match[to];
				if (visit[to_up]) continue;
				if (DFS(to_up)) {
					match[to] = i;
					return true;
				}
			}
		}
	}
	return false;
}