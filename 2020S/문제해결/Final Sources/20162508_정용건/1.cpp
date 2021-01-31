#include <iostream>
#include <vector>
using namespace std;

int res[3];//a :-1, b : 0, c: 1
int n;

vector<vector<int>> v;

void paper(int x, int y, int n) {//x, y : 시작, n : 범위
	//cout << x << y << n << endl;
	int x1, x2, x3, y1, y2, y3, newn = n, target, iscomp = 0;
	target = v[x][y];
	if (newn == 1) {
		res[target + 1]++;
		return;
	}
	newn /= 3;
	x1 = x; x2 = x + newn; x3 = x + newn * 2;
	y1 = y; y2 = y + newn; y3 = y + newn * 2;
	for (int i = x; i < x+n; i++) {
		for (int j = y; j < y+n; j++) {
			if (target != v[i][j]) {
				iscomp = 1;
				break;
			}
		}
	}
	if (iscomp == 1) {
		paper(x1, y1, newn);
		paper(x1, y2, newn);
		paper(x1, y3, newn);

		paper(x2, y1, newn);
		paper(x2, y2, newn);
		paper(x2, y3, newn);

		paper(x3, y1, newn);
		paper(x3, y2, newn);
		paper(x3, y3, newn);
	}
	else {
		res[target + 1]++;
	}
	return;
}


int main() {
	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			v[i].push_back(temp);
		}
	}

	paper(0, 0, n);

	//result
	for (int i = 0; i < 3; i++)
		cout << res[i] << endl;
	return 0;
}