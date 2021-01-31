#include <iostream>
#include <vector>

using namespace std;

int T, N, K;
long long answer;
bool not_prime[1121];
vector<int> prime;

long long dp[1121][15];

void make_prime() {
	for (int i = 2; i < 1121; i++) {
		if (!not_prime[i]) {
			prime.push_back(i);
			dp[i][1] = 1;
			for (int j = i * 2; j < 1121; j += i) {
				not_prime[j] = true;
			}
		}
	}
}

void make_dp() {
	int cur = 0;
	for (int i = 0; i < prime.size(); i++) {
		cur = prime.at(i);
		for (int k = 2; k <= 14; k++) {
			for (int j = 0; j < 1121; j++) {
				if (j - cur >= 0) {
					dp[j][k] += dp[j - cur][k - 1];
				}				
			}
		}
	}
}

int main() {
	cin >> T;

	make_prime();
	make_dp();

	for (int test = 1; test <= T; test++) {
		cin >> N >> K;

		cout << dp[N][K] << endl;
	}
}