#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAX_N 2222
#define MINUS 0
#define ZERO 1
#define PLUS 2

int N;
int board[MAX_N][MAX_N];
int ans[3];

void input() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
		}
	}
}

bool isSame(int y, int x, int length) {
	int cur = board[y][x];
	for (int i = y; i < y + length; i++) {
		for (int j = x; j < x + length; j++) {
			if (cur != board[i][j]) {
				return false;
			}
		}
	}

	return true;
}

void splitBoard(int y, int x, int length) {
	if (length == 1 || isSame(y, x, length)) {
		int op = -1;
		if (board[y][x] == -1) {
			op = MINUS;
		}
		else if (board[y][x] == 0) {
			op = ZERO;
		}
		else if (board[y][x] == 1) {
			op = PLUS;
		}

		ans[op]++;
		return;
	}

	int nextLength = length / 3;
	splitBoard(y, x, nextLength);
	splitBoard(y + nextLength, x, nextLength);
	splitBoard(y + 2 * nextLength, x, nextLength);
	splitBoard(y, x + nextLength, nextLength);
	splitBoard(y + nextLength, x + nextLength, nextLength);
	splitBoard(y + 2 * nextLength, x + nextLength, nextLength);
	splitBoard(y, x + 2 * nextLength, nextLength);
	splitBoard(y + nextLength, x + 2 * nextLength, nextLength);
	splitBoard(y + 2 * nextLength, x + 2 * nextLength, nextLength);
}

void output() {
	for (int i = 0; i < 3; i++) {
		printf("%d\n", ans[i]);
	}
}
int main() {
	input();
	splitBoard(0, 0, N);
	output();

	return 0;
}