#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define MAX 305

int dp[MAX];


int main(void) {
	//freopen("./ex.txt", "r", stdin);
	//freopen("./out.txt", "w+", stdout);

	memset(dp, 0, sizeof(dp));

	int N, M, K;

	scanf("%d %d %d", &N, &M, &K);

	vector<vector<int>> edges(N +1, vector<int>(N+1, -1));

	for (int k = 0; k < K; k++) {
		int a, b, c;

		scanf("%d %d %d", &a, &b, &c);
		if (a < b && edges[a][b] < c) {
			edges[a][b] = c;
		}
	}

	for (int b = 2; b <= M; b++) {
		for (int a = 1; a < b; a++) {
			if (edges[a][b] == -1)
				continue;

			int cur = dp[a] + edges[a][b];

			if (dp[b] < cur) {
				dp[b] = cur;
			}
		}
	}

	printf("%d\n", dp[M]);
	

	return 0;
}