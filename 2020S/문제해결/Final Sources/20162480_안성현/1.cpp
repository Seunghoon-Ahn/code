#include <cstdio>
#include <iostream>
using namespace std;
int N;
int arr[2188][2188];
int ocnt, zcnt, mcnt;
void solve(int x, int y, int n) {
	int i, j;
	int one = 0, zero = 0, minu = 0;
	for (i = x; i < x + n; i++)
		for (j = y; j < y + n; j++) {
			if (arr[i][j] == 1)
				one++;
			else if (arr[i][j] == -1)
				minu++;
			else if (arr[i][j] == 0)
				zero++;
		}
	if (one == n*n)
		ocnt++;
	else if (minu == n*n)
		mcnt++;
	else if (zero == n*n)
		zcnt++;
	else {
		solve(x, y, n / 3);

		solve(x, y + n / 3, n / 3);

		solve(x, y + 2 * (n / 3), n / 3);

		solve(x + n / 3, y, n / 3);
		solve(x + 2 * (n / 3), y, n / 3);

		solve(x + n / 3, y + n / 3, n / 3);

		solve(x + 2 * (n / 3), y + n / 3, n / 3);

		solve(x + n / 3, y + 2 * (n / 3), n / 3);

		solve(x + 2 * (n / 3), y + 2 * (n / 3), n / 3);
	}
}
int main() {
	cin >> N;
	int i, j;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			scanf("%d", &arr[i][j]);
	solve(1, 1, N);
	printf("%d\n%d\n%d\n", mcnt, zcnt, ocnt);
}