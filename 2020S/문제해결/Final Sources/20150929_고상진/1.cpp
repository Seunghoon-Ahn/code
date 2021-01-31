#include <iostream>

using namespace std;

int N;
int input[2187][2187];
int answer[3]; 
//index 0 : -1
//index 1 : 0
//index 2 : 1

void check(int col, int row, int len) {
	
	int num = input[col][row];
	bool allsame = true;
	for (int i = col; i < col + len; i++) {
		for (int j = row; j < row + len; j++) {
			if (num != input[i][j]) {
				allsame = false;
				break;
			}
		}
	}
	if (allsame) {
		answer[num + 1]++;
	}
	else {
		int len_new = len / 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				check(col + i * len_new, row + j * len_new, len_new);
			}
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input[i][j];
		}
	}
	
	check(0, 0, N);
	for (int i = 0; i < 3; i++) {
		cout << answer[i] << endl;
	}
}