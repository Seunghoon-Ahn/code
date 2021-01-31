#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int N, M, tmp;
int plate[100][100];
vector<pii> cheese;

int time;
int cheese_left;

void air_pollute(int i, int j) {
	if (i < 0 || i >= N || j < 0 || j >= M) return;
	if (plate[i][j] != 0) return;

	plate[i][j] = -(time + 1);
	air_pollute(i - 1, j);
	air_pollute(i + 1, j);
	air_pollute(i, j - 1);
	air_pollute(i, j + 1);
}

int is_pollute(int i, int j) {
	if (i < 0 || i >= N || j < 0 || j >= M) return 0;
	if (plate[i][j] >= -time && plate[i][j] < 0) return 1;
	return 0;
}

void check() {
	for (int i = 0; i < cheese.size(); i++) {
		if (plate[cheese.at(i).first][cheese.at(i).second] == 1) {
			tmp = 0;
			tmp += is_pollute(cheese.at(i).first - 1, cheese.at(i).second);
			tmp += is_pollute(cheese.at(i).first + 1, cheese.at(i).second);
			tmp += is_pollute(cheese.at(i).first, cheese.at(i).second - 1);
			tmp += is_pollute(cheese.at(i).first, cheese.at(i).second + 1);
			if (tmp >= 2) {
				plate[cheese.at(i).first][cheese.at(i).second] = 0;
				air_pollute(cheese.at(i).first, cheese.at(i).second);
				cheese_left--;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> plate[i][j];
			if (plate[i][j] == 1) {
				cheese.push_back({ i, j });
				cheese_left++;
			}
		}
	}

	for (int j = 0; j < M; j++) {
		if (plate[0][j] == 0) {
			air_pollute(0, j);
		}
		if (plate[N - 1][j] == 0) {
			air_pollute(N - 1, j);
		}
	}
	for (int i = 0; i < N; i++) {
		if (plate[i][0] == 0) {
			air_pollute(i, 0);
		}
		if (plate[i][M - 1] == 0) {
			air_pollute(i, M - 1);
		}
	}

	time = 1;
	while (cheese_left > 0) {
		check();
		time++;
	}
	cout << time - 1;
}