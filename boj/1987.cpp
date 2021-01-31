#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
int check[27] = {0, };
char f[21][21] = {0, };
int dx[4] = {0, -1, 1, 0};
int dy[4] = {-1, 0, 0, 1};
int r, c;

int calcul(int curx, int cury, int cnt) {
	int res = 0;
	check[f[curx][cury] - 'A'] = 1;

	for(int i = 0; i < 4; i++) {
		int newx = curx + dx[i];
		int newy = cury + dy[i];	
		if(0 <= newx && newx < r && 0 <= newy && newy < c && (check[f[newx][newy] - 'A'] == 0))
			res = max(res, calcul(newx, newy, cnt + 1));
	}
	check[f[curx][cury] - 'A'] = 0;
	return res + 1;
}

int main(void) {
	memset(f, 0, sizeof(f));
	memset(check, 0, sizeof(check));

	cin >> r >> c;
	for(int i = 0; i < r; i++) {
		string tmp;
		cin >> tmp;
		for(int j = 0; j < c; j++) {
			f[i][j] = tmp[j];
		}
	}
	printf("%d\n", calcul(0, 0, 1));

	return 0;
}

