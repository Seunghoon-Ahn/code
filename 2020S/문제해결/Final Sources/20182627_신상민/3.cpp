#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

//풀지 못했습니다.

int n, k;
int dp[15][1121];
int isPrime[1121] = { false };

void setPrime() {
	int sm = sqrt(1121);
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[1] = 0;
	for (int i = 2; i <= sm; i++) {
		if (isPrime[i]) {
			for (int j = 2;; j++) {
				int mul = i * j;
				if (mul > 1120)
					break;
				isPrime[mul] = 0;
			}
		}
	}
}

int main() {
	setPrime();
	int t;
	cin >> t;
	while (t--) { //dp[k][n] = dp[k-1][n-p] +1
		cin >> n >> k;
		for (int i = 1; i <= k; i++) { //k
			for (int j = 2; j <= n; j++) {
				for (int p = 2; p <= n / 2; p++) {
					if (isPrime[p])
						dp[i][j] += dp[i - 1][j - p];
				}
			}
		}
		cout << dp[k][n] << '\n';
	}

	//소수 테스트
	/*for (int i = 1; i <= 1120; i ++) {
	cout << i << ':';
	if (isPrime[i])
	cout << "True" << '\n';
	else
	cout << "False" << '\n';
	}*/

	return 0;
}