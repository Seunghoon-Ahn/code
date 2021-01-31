#include<stdio.h>
#include<iostream>

using namespace std;

const int MAX = 2500;

int board[MAX][MAX];
int mi = 0;
int zero = 0;
int one = 0;

void slice(int hang, int yul, int n);

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
		}
	}

	slice(0, 0, n);

	printf("%d\n%d\n%d\n", mi, zero, one);
	cin >> n;
}

void slice(int hang, int yul, int n)
{
	bool check = false;
	int cnt = 0;
	int square = n*n;

	int now = board[hang][yul];	//지금 보는거

	if (n == 1) {
		if (now == -1)
			mi++;
		else if (now == 0)
			zero++;
		else
			one++;
	}
	else {
		for (int i = hang; i < hang + n; i++) {	//사각형검사
			for (int j = yul; j < yul + n; j++) {
				if (now == board[i][j]) {
					cnt++;
				}
			}
		}

		if (cnt == square) {	//사각형만족하면
			if (now == -1)
				mi++;
			else if (now == 0)
				zero++;
			else
				one++;
		}
		else {	//9장으로 자르기
			slice(hang, yul, n / 3);
			slice(hang, yul + n / 3, n / 3);
			slice(hang, yul + n / 3 + n / 3, n / 3);

			slice(hang + n / 3, yul, n / 3);
			slice(hang + n / 3, yul + n / 3, n / 3);
			slice(hang + n / 3, yul + n / 3 + n / 3, n / 3);

			slice(hang + n / 3 + n / 3, yul, n / 3);
			slice(hang + n / 3 + n / 3, yul + n / 3, n / 3);
			slice(hang + n / 3 + n / 3, yul + n / 3 + n / 3, n / 3);
		}
	}
}