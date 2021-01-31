// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

int n;

int arr[3];

int map[2430][2430];

void go(int x, int y, int k) {
	int firstnum = map[x][y];

	if (k == 1) {
		arr[firstnum + 1]++;
		return;
	}

	bool check = true;
	for (int i = x; i < x + k; i++) {
		for (int j = y; j < y + k; j++) {
			if (firstnum != map[i][j]) {
				check = false;
				break;
			}
		}
		if (!check) {
			break;
		}
	}

	if (!check) {
		go(x, y, k / 3);
		go(x , y + k / 3, k / 3);
		go(x, y + 2*k / 3, k / 3);
		go(x + k/3, y, k / 3);
		go(x + k / 3, y + k / 3, k / 3);
		go(x + k / 3, y + 2 * k / 3, k / 3);
		go(x + 2*k / 3, y, k / 3);
		go(x +2* k / 3, y + k / 3, k / 3);
		go(x +2* k / 3, y + 2 * k / 3, k / 3);

	}
	else {
		arr[firstnum + 1]++;
	}

}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j< n; j++) {
			cin >> map[i][j];
		}
	}

	go(0, 0, n);

	for (int i = 0; i < 3; i++) {
		cout << arr[i] << '\n';
	}

    return 0;
}

