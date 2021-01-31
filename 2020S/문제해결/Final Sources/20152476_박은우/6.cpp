#include <cstdio>
using namespace std;

int n, m;
int paper[101][101];
int time[101][101];
int visited[101][101];

void checkWall(int r, int c) {
	if (r < 0 || c < 0 || r >= n || c >= m) return;
	if (paper[r][c] == 1) {
		time[r][c]++;
		visited[r][c] = 1;
		return;
	}
	if (visited[r][c] == 1) return;
	visited[r][c] = 1;

	checkWall(r - 1, c);
	checkWall(r, c - 1);
	checkWall(r + 1, c);
	checkWall(r, c + 1);
}

int meltCheese() {
	int num = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (time[i][j] >= 2) {
				num++;
				paper[i][j] = 0;
			}
			visited[i][j] = 0;
			time[i][j] = 0;
		}
	}
	return num;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &paper[i][j]);
		}
	}
	int answer = 0;
	int num = 1;
	while (num) {
		checkWall(0, 0);
		num = meltCheese();
		answer++;
	}
	printf("%d", answer - 1);
	return 0;
}