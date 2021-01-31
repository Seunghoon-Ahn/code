#include <stdio.h>
#include <vector>
#include <math.h>
#define N 3000
using namespace std;

int num;
int a[N][N];
int ans[3];

bool same(int, int, int, int);
void dc(int r, int c,int n ) {
	
	if (n == 1) {
		ans[a[r][c] + 1] ++;
		return;
	}
	if (same(r, c, n, a[r][c])) {
		ans[a[r][c] + 1]++;
		return;
	}
	int nn = n / 3;
	for (int i = 0; i < n; i += nn) {
		for (int j = 0; j < n; j += nn) {
			dc(r + i, c + j, nn);
		}
	}

}
bool same(int r, int c, int n,int t) {
	for (int i = r; i < r + n; i++) {
		for (int j = c; j < c + n; j++) {
			if (a[i][j] != t)
				return false;
		}
	}
	return true;
}
int main() {
	
	scanf("%d", &num);
	for (int i = 1; i <= num; i++){
		for (int j = 1; j <= num; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	dc(1, 1, num);
	for (int i = 0; i < 3; i++)
		printf("%d\n", ans[i]);
}