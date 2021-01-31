#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAX_N 1121
#define MAX_K 15

using namespace std;
using lint = long long;

int TC;
int N, K;
int ans;
bool isPrime[MAX_N];
int primes[MAX_N];
int primesIndexMax;
int tmp[MAX_N];
lint dp[MAX_N][MAX_K];

void input() {
	scanf("%d %d", &N, &K);
	ans = 0;
}

void eratos() {
	int range = (int)sqrt(MAX_N);
	for (int i = 2; i<=range; i++) {
		if (isPrime[i]) {
			for (int j = i * 2; j < MAX_N; j+=i) {
				isPrime[j] = false;
			}
		}
	}
	int j = 0;
	for (int i = 2; i < MAX_N; i++) {
		if (isPrime[i]) {
			primes[j++] = i;
		}
	}
	primesIndexMax = j - 1;
}

void init() {
	memset(isPrime, 1, sizeof(isPrime));
	eratos();
}

lint findDp(int n, int k, int primeIndex) {
	if (dp[n][k] != -1) return dp[n][k];
	
	// 이전 점화식으로 가기
	lint curVal = 0;
	for (int i = primeIndex; i >= 0; i--) {
		if (primes[i] <= n) {
			curVal += findDp(n - primes[i], k - 1, primeIndex - 1);
		}
	}

	return dp[n][k] = curVal;
}

void findPrimeFactorialzation(int n, int k) {
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < N; i++) {
		dp[i][0] = 0;
		if (isPrime[i]) {
			dp[i][1] = 1;
		}
	}
	findDp(n, k, primesIndexMax);
}

void output() {
	printf("%lld\n", dp[N][K]);
}
int main() {
	scanf("%d", &TC);
	init();
	for (int i = 0; i < TC; i++) {
		input();
		findPrimeFactorialzation(N, K);
		output();
	}

	return 0;
}