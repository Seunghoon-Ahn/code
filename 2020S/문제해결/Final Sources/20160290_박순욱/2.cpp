#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

#define MAX 100000

int N, M;
int desk[MAX + 1] = { 0, };

bool isOkay(long long);

int main() {
	scanf("%d %d", &N, &M);
	int maxDesk = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &desk[i]);
		maxDesk = max(maxDesk, desk[i]);
	}

	long long left = 0, right = maxDesk * M;
	long long mid, minV = right;

	while (left <= right) {
		mid = (left + right) / 2;
		if (isOkay(mid)) {
			minV = min(minV, mid);
			right = mid - 1;
		}
		else
			left = mid + 1;
	}

	printf("%lld\n", minV);

	return 0;
}

bool isOkay(long long time) {
	long long num = 0;
	for (int i = 0; i < N; i++) {
		num += (time / (long long)desk[i]);
	}

	return num >= (long long)M;
}