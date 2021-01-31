#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int N, M;

#define Y first
#define X second

bool bound_check(int n, int m) {
	return n >= 0 && m >= 0 && n < N && m < M;
}

int main(void) {
	//freopen("./ex.txt", "r", stdin);
	//freopen("./out.txt", "w+", stdout);

	pair<int,int> v[4];

	v[0] = make_pair(0, 1);
	v[1] = make_pair(0, -1);
	v[2] = make_pair(1, 0);
	v[3] = make_pair(-1, 0);

	queue<pair<int, int>> airQ;
	queue<pair<int, int>> cheeseQ;
	queue<pair<int, int>> eliminateQ;

	scanf("%d %d", &N, &M);

	vector<vector<bool>> visited(N, vector<bool>(M, false));
	vector<vector<bool>> is_cheese(N, vector<bool>(M, false));
	
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			int cur;
			scanf("%d", &cur);

			is_cheese[n][m] = (cur == 1);
		}
	}

	airQ.push(make_pair(0, 0));
	visited[0][0] = true;
	

	int time = 0;

	while (true) {
		while (!airQ.empty()) {
			pair<int,int> cur = airQ.front();
			
			airQ.pop();

			for (int i = 0; i < 4; i++) {
				int next_y = cur.Y + v[i].Y;
				int next_x = cur.X + v[i].X;

				//printf("%d %d %d %d %d %c\n",time, cur.Y, cur.X, next_y, next_x, bound_check(next_y, next_x) ? 'O' : 'X');

				if (bound_check(next_y, next_x) && visited[next_y][next_x] == false) {

					if (is_cheese[next_y][next_x]) {
						cheeseQ.push(make_pair(next_y, next_x));
					}
					else {
						airQ.push(make_pair(next_y, next_x));
					}
					visited[next_y][next_x] = true;
				}
			}
		}

		if (cheeseQ.empty())
			break;

		while (!cheeseQ.empty()) {

			pair<int, int> cur = cheeseQ.front();
			cheeseQ.pop();

			int near_air_cnt = 0;

			for (int i = 0; i < 4; i++) {
				int next_y = cur.Y + v[i].Y;
				int next_x = cur.X + v[i].X;
				if (visited[next_y][next_x] && !is_cheese[next_y][next_x]) {
					near_air_cnt++;
				}
			}

			if (near_air_cnt >= 2) {
				eliminateQ.push(cur);
				airQ.push(cur);
			}
			else {
				visited[cur.Y][cur.X] = false;
			}
		}

		while (!eliminateQ.empty()) {
			pair<int, int> cur = eliminateQ.front();
			eliminateQ.pop();
			is_cheese[cur.Y][cur.X] = false;
		}

		time++;
	}

	printf("%d\n", time);

	return 0;
}