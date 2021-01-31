#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MN = 3010;

int arr[MN][MN];
int res[4];

bool check(int x1, int y1, int x2, int y2)
{
	int tmp = arr[x1][y1];
	for (int i = x1; i < x2; i++) {
		for (int j = y1; j < y2; j++) {
			if (tmp != arr[i][j])
				return false;
		}
	}
	return true;
}

void dnc(int x1, int y1, int x2, int y2)
{
	if ((x2-x1 == 1 && y2-y1 == 1) || check(x1, y1, x2, y2)) {
		res[arr[x1][y1] + 1]++;
	}
	else {
		dnc(x1, y1, x1 + (x2 - x1) / 3, y2 / 3);
		dnc(x1 + ((x2 - x1) / 3), y1, x1 + 2 * ((x2 - x1) / 3), y2/3);
		dnc(x1 + 2 * ((x2 - x1) / 3), y1, x2, y2 / 3);
		dnc(x1, y1 + ((y2 - y1) / 3), x1 + (x2 - x1) / 3, y1 + 2 * ((y2 - y1) / 3));
		dnc(x1 + ((x2 - x1) / 3), y1 + ((y2 - y1) / 3), x1 + 2 * ((x2 - x1) / 3), y1 + 2 * ((y2 - y1) / 3));
		dnc(x1 + 2*((x2 - x1) / 3), y1 + (y2 - y1) / 3, x2, y1 + 2 * ((y2 - y1) / 3));
		dnc(x1, y1 + 2*((y2 - y1) / 3), x1 + (x2 - x1) / 3, y2);
		dnc(x1 + ((x2 - x1) / 3), y1 + 2 * ((y2 - y1) / 3), x1 + 2 * ((x2 - x1) / 3), y2);
		dnc(x1 + 2*((x2 - x1) / 3), y1 + 2 * ((y2 - y1) / 3), x2, y2);
	}
}

int main(void)
{
	int N;	cin >> N;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			cin >> arr[i][j];
	dnc(0, 0, N, N);

	cout << res[0] << '\n';
	cout << res[1] << '\n';
	cout << res[2] << '\n';
}