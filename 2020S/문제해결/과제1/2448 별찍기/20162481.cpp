#include <iostream>
using namespace std;

void print(int n, int x, int y);

char map[4000][7000];

int main(void) {
	int N;
	cin >> N;
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 2 * N; j++)
			map[i][j] = ' ';
	
	print(N, N - 1, 0);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2 * N; j++)
			cout << map[i][j];
		cout << '\n';
	}
	return 0;
}

void print(int high, int x, int y) {
	if (high == 3) {
		map[y][x] = '*';             //삼각형
		
		map[y+1][x-1] = '*';
		map[y+1][x] = ' ';
		map[y+1][x+1] = '*';
		
		map[y+2][x-2] = '*';
		map[y+2][x-1] = '*';
		map[y+2][x] = '*';
		map[y+2][x+1] = '*';
		map[y+2][x+2] = '*';
	}
	else {
		print(high / 2, x, y);  //위
		print(high / 2, x - (high / 2),y + (high / 2));   //왼
		print(high / 2, x + (high / 2), y + (high / 2));  //오
	}
}