#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 2200
int N;
int arr[MAX][MAX];
int z_cnt=0, one_cnt=0, n_one_cnt=0;

void divine(int x, int y, int size) {
	if (size == 1) {
		if (arr[x][y] == 1) {
			one_cnt += 1;
		}
		else if (arr[x][y] == 0) {
			z_cnt += 1;
		}
		else if (arr[x][y] == -1) {
			n_one_cnt += 1;
		}
		return;
	}
	int z_idx = 0;
	int o_idx = 0;
	int n_idx = 0;
	for (int i = x; i < x + size; i++) {
		for (int j = y; j < y + size; j++) {
			if (arr[i][j] == 1) {
				o_idx += 1;
			}
			else if(arr[i][j] == 0) {
				z_idx += 1;
			}
			else if (arr[i][j] == -1) {
				n_idx += 1;
			}
		}
	}
	if (o_idx == size*size) {
		one_cnt += 1;
	}else if (z_idx == size*size) {
		z_cnt += 1;
	}
	else if (n_idx == size*size) {
		n_one_cnt += 1;
	}
	else {
		divine(x, y, size / 3); // 0,0
		divine(x, y + size / 3, size / 3); //0,1
		divine(x, y + (size * 2) / 3, size / 3); // 0,2
		divine(x + size / 3, y, size / 3);
		divine(x + size / 3, y + size / 3, size / 3);
		divine(x + size / 3, y + (size * 2) / 3, size / 3);
		divine(x + (size * 2) / 3, y, size / 3);
		divine(x + (size * 2) / 3, y + size / 3, size / 3);
		divine(x + (size * 2) / 3, y + (size * 2) / 3, size / 3);
	}
	return;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int tmp;
			cin >> tmp;
			arr[i][j] = tmp;
		}
	}
	divine(0, 0, N);
	cout << n_one_cnt << endl;
	cout << z_cnt << endl;
	cout << one_cnt << endl;
	return 0;
}