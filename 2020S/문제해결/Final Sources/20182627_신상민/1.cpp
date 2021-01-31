#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int map[2188][2188];
int n;

int numOf[3];

void dc(int y, int x, int len) {
	bool isSame = true;
	int tmp = map[y][x];
	for (int i = y; i < y + len; i++) {
		for (int j = x; j < x + len; j++) {
			if (map[i][j] != tmp)
				isSame = false;
		}
	}

	if (isSame) {
		numOf[tmp + 1]++;
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				dc(y + i*len / 3, x + j*len / 3, len / 3);
			}
		}
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	dc(1, 1, n);

	for (int i = 0; i < 3; i++) {
		cout << numOf[i] << '\n';
	}

	return 0;
}