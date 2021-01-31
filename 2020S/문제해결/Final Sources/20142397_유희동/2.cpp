#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAX_N 100001
#define INF 1234567890
using namespace std;
using lint = long long;

int N, M;
int checker[MAX_N];
lint ans;
lint minElement = INF;

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &checker[i]);
		if (minElement > checker[i]) {
			minElement = checker[i];
		}
	}
}

void init() {
	ans = minElement * M;
}

bool isCheckable(lint val) {
	lint curCnt = 0;
	for (int i = 0; i < N; i++) {
		curCnt += (val / checker[i]);
	}

	// curCnt 가 M보다 크거나 같다면 트루
	return curCnt >= M;
}

void parametricSearch(lint left, lint right) {
	if (left > right) return;
	lint mid = (left + right) / 2;

	if (isCheckable(mid)) {
		if (mid < ans) {
			ans = mid;
		}
		parametricSearch(left, mid - 1);
	}
	else {
		parametricSearch(mid + 1, right);
	}
}


void output() {
	printf("%lld", ans);
}
int main() {
	input();
	init();
	parametricSearch(0, minElement * M);
	output();

	return 0;
}