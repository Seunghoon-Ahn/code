#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N, M, K;
vector<pair<int, int>> R[301];
int C[301];
bool visit[301];

int Bell_Fo();

int main(void)
{
	int a, b, c;
	int res;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a < b)
			R[a].push_back({ b, c });
	}
	for (int i = 2; i <= N; i++)
		C[i] = 0;

	res = Bell_Fo();
	printf("%d", res);
}

int Bell_Fo() {
	for (pair<int, int> p : R[1])
		if (C[p.first] < p.second)
		C[p.first] = p.second;

	for (int i = 2; i <= M - 1; i++) {

		memset(visit + 1, true, N);
		for (int j = 1; j <= N; j++)
			if (C[j] == 0)
				visit[j] = false;

		for (int j = 1; j <= N; j++)
			if (visit[j])
				for (pair<int, int> p : R[j]) {
					if (C[p.first] < C[j] + p.second) {
						C[p.first] = C[j] + p.second;
					}
				}
	}

	return C[N];
}