#include <stdio.h>
#include <string.h>

#include <vector>

using namespace std;

int answer[3];

int find_answer(vector<vector<int>>& v, int y, int x, int size) {
	if (size == 1) {
		return v[y][x];
	}

	int val[9];

	int next_size = size / 3;

	for (int t = 0; t < 9; t++) {
		val[t] = find_answer(v, y + (t / 3) * next_size, x + (t % 3) * next_size, next_size);
	}

	int ret = val[0];

	for (int t = 1; t < 9; t++) {
		if (val[t] != ret) {
			ret = 100;
			break;
		}
	}

	if (ret == 100) {
		for (int t = 0; t < 9; t++) {
			if (val[t] < 2) {
				answer[val[t] + 1] ++;
			}
		}
	}

	return ret;
	

}

int main()
{
	int N;

	scanf("%d", &N);

	memset(answer, 0, sizeof(answer));

	vector<vector<int>> v(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &(v[i][j]));
		}
	}

	int val = find_answer(v, 0, 0, N);
	if (val < 2) {
		answer[val + 1] ++;
	}

	for (int i = 0; i < 3; i++) {
		printf("%d\n", answer[i]);
	}


    return 0;
}

