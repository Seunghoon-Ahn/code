#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int MAX = 2187;

int N, m[MAX][MAX];
int zero = 0, one = 0, minus = 0;

bool sq(int i, int j, int n) {
	for (int k = 0; k < n / 3; k++) {
		for (int h = 0; h < n / 3; h++)
			if (m[i + k][j + h] != m[i][j])
				return false;
	}
	return true;
}

void f(int x, int y, int n) {
	for (int i = x; i < x + n; i += n / 3) {
		for (int j = y; j < y+ n; j += n / 3) {
			if (sq(i, j, n)) {
				if (m[i][j] == 0)
					zero++;
				else if (m[i][j] == 1)
					one++;
				else if (m[i][j] == -1)
					minus++;
			}
			else {
				f(i, j, n / 3);
			}
		}
	}
}


int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num;
			scanf("%d", &num);
			m[i][j] = num;
		}
	}

	if (sq(0, 0, 3 * N)) {
		if (m[0][0] == 0)
			zero++;
		else if (m[0][0] == 1)
			one++;
		else if (m[0][0] == -1)
			minus++;
	}
	else {
		f(0, 0, N);
	}

	printf("%d %d %d", minus, zero, one);
}