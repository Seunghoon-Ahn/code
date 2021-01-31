#include <iostream>
#include <algorithm>

using namespace std;

int N, answer;
int abil[20][20];
bool isA[20];

void solve(int cur, int scoreA, int scoreB, int numA, int numB) {
	if (cur == N) {
		if (numA == N / 2) {
			answer = min(answer, abs(scoreA - scoreB));
		}
	}
	else if (numA > N / 2 || numB > N / 2) {
		return;
	}
	else {
		int add_B = 0;
		for (int i = 0; i < cur; i++) {
			if (!isA[i]) {
				add_B += abil[i][cur] + abil[cur][i];
			}
		}
		solve(cur + 1, scoreA, scoreB + add_B, numA, numB + 1);
		int add_A = 0;
		for (int i = 0; i < cur; i++) {
			if (isA[i]) {
				add_A += abil[i][cur] + abil[cur][i];
			}
		}
		isA[cur] = true;
		solve(cur + 1, scoreA + add_A, scoreB, numA + 1, numB);
		isA[cur] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> abil[i][j];
		}
	}
	isA[0] = true;
	answer = 987654321;
	solve(1, 0, 0, 1, 0);
	cout << answer;
}
