#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

#define INF 1000000001

int T;
int N, K;
int result;
std::vector<int> primes;
int visit[1200];
int dp[20][1200];

int func(int n, int index, int restK) {
	int result = N - n;

	if (result == 0) {
		result++;
		return true;
	}

	if (restK == 0) {
		return false;
	}

	for (int i = index; i < primes.size(); i++) {
		func(n - primes[i], index, restK - 1);
	}
}

int main() {
	for (int i = 2; i <= 1120; i++) {
		if (!visit[i]) {
			primes.push_back(i);
			dp[1][i] = 1;
			for (int j = i; j <= 1120; j += i) {
				visit[j] = 1;
			}
		}
	}

	for ()

	scanf("%d", &T);

	while (T--) {
		result = 0;
		scanf("%d %d", &N, &K);

		func(0, 0, K);
		printf("%d\n", result);
	}
	return 0;
}
/*
12
24 3
24 2
2 1
1 1
4 2
18 3
17 1
17 3
17 4
100 5
1000 10
1120 14

*/