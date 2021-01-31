#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

int N;
int map[5000][5000];
int z, m, p;

int func(int y, int x, int size) {
	if (size == 1) {
		switch (map[y][x]) {
		case -1:
			m++;
			break;

		case 0:
			z++;
			break;

		case 1:
			p++;
			break;
		}
		return map[y][x];
	}

	int divide = size / 3;
	int l_z = 0;
	int l_m = 0;
	int l_p = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (func(y + i * divide, x + j * divide, divide)) {
			case -1:
				l_m++;
				break;
				
			case 0:
				l_z++;
				break;

			case 1:
				l_p++;
				break;
			}
		}
	}

	if (l_m == 9) {
		m -= 8;
		return -1;
	}
	else if (l_z == 9) {
		z -= 8;
		return 0;
	}
	else if (l_p == 9) {
		p -= 8;
		return 1;
	}

	return 2;
}

int main() {
	scanf("%d", &N);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf("%d", &map[y][x]);
		}
	}

	func(0, 0, N);

	printf("%d\n%d\n%d", m, z, p);
	return 0;
}
/*

9
0 0 0 1 1 1 -1 -1 -1 
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
0 1 -1 0 1 -1 0 1 -1
0 1 -1 0 1 -1 0 1 -1
0 1 -1 0 1 -1 0 1 -1



9
0 0 1 0 0 1 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 1 0 0 1 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 1 0 0 1 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0


3
1 1 1
1 1 1
1 1 1
*/