#include <iostream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <vector>
using namespace std;

#define MAX 1121

int numSet[MAX];
vector<int> prime;
int T, N, K;
long long cnt = 0;

void cp() {
	memset(numSet, -1, sizeof numSet);
	numSet[0] = 1;
	numSet[1] = 1;
	for (int i = 2; i < sqrt(MAX); i++) {
		for (int j = 2; j < MAX; j++) {
			if (i*j > MAX) break;
			numSet[i*j] = 1;
		}
	}
	for (int i = 0; i < MAX; i++) {
		if (numSet[i] == -1) {
			prime.push_back(i);
		}
	}
	return;
}

void knapsack(int idx, int sum,long long mem) {
	if (sum == N && mem == K) {
		cnt++;
		return;
	}
	if (idx < prime.size() && mem <= K) {
		sum += prime[idx];
		if (sum > N) {
			return;
		}
		else {
			knapsack(idx + 1, sum, mem + 1);
			knapsack(idx + 1, sum - prime[idx], mem);
		}
		
	}
}

int main() {
	cp();
	cin >> T;
	for (int cs = 0; cs < T; cs++) {
		cin >> N >> K;
		cnt = 0;
		knapsack(0,0,0);
		if (N == 1) {
			cout << 0 << endl;
			continue;
		}
		cout << cnt << endl;
	}
	return 0;
}