#include <cstdio>
using namespace std;

int n;
char paper[2188][2188];
int count[3];

char slice(int r, int c, int size) {
	if (size == 1) return paper[r][c];
	char result[3][3];
	int cnt[3] = { 0, };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = slice(r + (i*size / 3), c + (j*size / 3), size / 3);
			switch (result[i][j]) {
			case -1: cnt[0]++; break;
			case 0: cnt[1]++; break;
			case 1: cnt[2]++; break;
			}
		}
	}
	if (cnt[0] == 9 || cnt[1] == 9 || cnt[2] == 9) {
		if (size == n) {
			for (int i = 0; i < 3; i++) {
				count[i] += cnt[i]/9;
			}
		}
		return paper[r][c];
	}
	for (int i = 0; i < 3; i++) {
		count[i] += cnt[i];
	}
	return 3;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &paper[i][j]);
		}
	}

	slice(0, 0, n);

	for (int i = 0; i < 3; i++) {
		printf("%d\n", count[i]);
	}
	
	return 0;
}