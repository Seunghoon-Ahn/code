#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int map[2200][2200];
int N;
int under_zero = 0, zero = 0, one = 0;

void cut(int x, int y, int len);

int main(void)
{
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	cut(0, 0, N);

	cout << under_zero << '\n';
	cout << zero << '\n';
	cout << one << '\n';

	return 0;
}

void cut(int x, int y, int len) {
	int tmp1 = 0, tmp2 = 0, tmp3 = 0; //°¢°¢ -1 , 0, 1 °¹¼ö
	for (int i = x; i < x + len; i++) {
		for (int j = y; j < y + len; j++) {
			if (map[i][j] == -1)
				tmp1++;
			else if (map[i][j] == 0)
				tmp2++;
			else if (map[i][j] == 1)
				tmp3++;
		}
	}
	if (tmp1 == len * len)
		under_zero++;
	else if (tmp2 == len * len)
		zero++;
	else if (tmp3 == len * len)
		one++;
	else {
		int div = len / 3;
		cut(x, y, div);
		cut(x, y + div, div);
		cut(x, y + 2 * div, div);
		cut(x + div, y, div);
		cut(x + div, y + div, div);
		cut(x + div, y + 2 * div, div);
		cut(x + div * 2, y, div);
		cut(x + div * 2, y + div, div);
		cut(x + div * 2, y + 2 * div, div);
	}
}