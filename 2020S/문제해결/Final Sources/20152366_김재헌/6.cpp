#include <iostream>

#define VAC 0
#define AIR 2
#define CHE 1

void init(int x, int y);
void melt(int x, int y);

int H[100][100];
int N, M;

int main(void)
{
	bool isend = false;
	int res;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &H[i][j]);

	init(0, 0);

	res = 0;
	while (!isend) {
		isend = true;

		for (int i = 1; i < N - 1; i++)
			for (int j = 1; j < M - 1; j++)
				melt(i, j);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				init(i, j);
				if (H[i][j] != AIR)
					isend = false;
			}

		res++;
	}

	printf("%d", res);
}

void init(int x, int y) {
	if (H[x][y] == VAC)
		if ((x == 0 && y == 0) || 
			(x + 1 < N) && H[x + 1][y] == AIR ||
			(x - 1 >= 0) && H[x - 1][y] == AIR ||
			(y + 1 < M) && H[x][y + 1] == AIR ||
			(y - 1 >= 0) && H[x][y - 1] == AIR) {

			H[x][y] = AIR;
			if (x + 1 < N)
				init(x + 1, y);
			if (x - 1 >= 0)
				init(x - 1, y);
			if (y + 1 < M)
				init(x, y + 1);
			if (y - 1 >= 0)
				init(x, y - 1);
		}
}

void melt(int x, int y) {
	int cnt = 0;
	if (H[x][y] != CHE)
		return;

	if (x + 1 < N)
		if (H[x + 1][y] == AIR)
			cnt++;
	if (x - 1 >= 0)
		if (H[x - 1][y] == AIR)
			cnt++;
	if (y + 1 < M)
		if (H[x][y + 1] == AIR)
			cnt++;
	if (y - 1 >= 0)
		if (H[x][y - 1] == AIR)
			cnt++;

	if (cnt >= 2)
		H[x][y] = VAC;
}