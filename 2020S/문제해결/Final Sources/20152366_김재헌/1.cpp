#include <iostream>

int H[2200][2200];
int N;
int ans[3] = { 0,0,0 };

void check_squ(int x, int y, int size);

int main(void)
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &H[i][j]);

	check_squ(0, 0, N);

	printf("%d %d %d", ans[0], ans[1], ans[2]);
}

void check_squ(int x, int y, int size)
{
	int tmp = -2;
	if (size == 1) {
		ans[H[x][y] + 1]++;
		return;
	}

	for (int i = x; i < x + size; i++)
		for (int j = y; j < y + size; j++) {
			if (tmp == -2)
				tmp = H[i][j];
			else if (H[i][j] != tmp) {
				for (int k = 0; k < 3; k++)
					for (int m = 0; m < 3; m++)
						check_squ(x + k*size / 3, y + m*size / 3, size / 3);
				return;
			}
		}

	ans[tmp + 1]++;
}