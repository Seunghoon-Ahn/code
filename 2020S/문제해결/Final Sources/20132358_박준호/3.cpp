#include <stdio.h>
#include <string.h>
#include <vector>

#define MAX 1200

using namespace std;

bool is_not_prime[MAX];

int dp[200][15][MAX];

int num = 0;

int main(void) {

	int T;

	//freopen("./ex.txt", "r", stdin);
	//freopen("./out.txt", "w+", stdout);

	memset(is_not_prime, 0, sizeof(is_not_prime));

	vector<int> v(1);
	v[0] = -1;

	is_not_prime[0] = true;
	is_not_prime[1] = true;

	for (int i = 2; i < MAX; i++) {
		if (is_not_prime[i] == false) {
			v.push_back(i);
			for (int j = i + i; j < MAX; j += i) {
				is_not_prime[j] = true;
			}
		}
	}

	
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		int N, K;

		scanf("%d %d", &N, &K);

		memset(dp, 0, sizeof(dp));

		dp[0][0][0] = 1;

		for (int p = 1; v[p] <= N; p++) {
			for (int k = 0; k < K;  k++) {
				for (int n = 0; n <= N; n++) {
					if (n + v[p] <= N) {
						dp[p][k + 1][n + v[p]] += dp[p - 1][k][n];
					}
					dp[p][k][n] += dp[p - 1][k][n];
				}
			}
		}
		
		int sum = 0;

		for (int p = 1; v[p] <= N; p++) {

			sum += dp[p][K][N];
			
		}

		printf("%d\n", sum);

	} 
	

	return 0;
}