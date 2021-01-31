#include <cstdio>
#include <vector>
using namespace std;

int n, m, k;
int answer = 0;
int city[301][301] = { 0, };
void dfs(int cur, int step, int score) {
	if (cur == n && step <= m) {
		if (answer < score) answer = score;
		return;
	}
	if (step == m) return;
	for (int i = cur + 1; i <= n; i++) {
		if (city[cur][i]) {
			dfs(i, step + 1, score + city[cur][i]);
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	int b, e, c;
	for (int i = 0; i < k; i++) {
		scanf("%d %d %d", &b, &e, &c);
		if (city[b][e] < c) {
			city[b][e] = c;
		}
	}
	dfs(1, 0, 0);
	printf("%d", answer);
	return 0;
}