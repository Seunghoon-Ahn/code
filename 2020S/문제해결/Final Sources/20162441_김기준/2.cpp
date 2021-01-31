#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
using namespace std;

const int M_MAX = 1e9;

int N, M, T[M_MAX + 1], t[M_MAX + 1];

void time(int n) {
	if (n == 0)
		exit(0);
	int p = M / N;
	int np = p;
	int alpha = M % N;
	while (T[n - 1] * p > T[n - 2] * p) {
		for (int i = 0; i < N; i++) {
			np--;
			p++;
			t[n - 1] = T[n - 1] * np;
			t[i] = T[i] * p;
		}
	}
	time(n - 1);
	exit(1);
}

int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		int t;
		scanf("%d", &t);
		T[i] = t;
	}
	sort(T, T + M_MAX + 1);
	time(N);
	sort(t, t + M_MAX + 1);

	printf("%d", t[0]);
}
