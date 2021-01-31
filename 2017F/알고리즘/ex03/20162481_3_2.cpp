//23 spheap
#include <iostream>
#include <queue>
#include <utility>
#include <climits>
#include <functional>
using namespace std;

int G[201][201] = { 0 };
int D[201][201] = { 0 };

typedef struct node {
	int lx;
	int ly;
	int value;
}NODE;


bool operator < (node t, node u) {
	return t.value > u.value;
}
priority_queue< node > q;

int count_node(node a) {
	int tmp = 100;
	if (a.lx == 1)
		tmp += 1;
	if (a.ly == 1)
		tmp += 10;
	return tmp;
}



int main(void) {
	int x, y = 0;
	int m = 0, n = 0;
	int sx, sy = 0;
	int ex, ey = 0;
	int res = 0;


	cin >> x >> y;
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			cin >> G[i][j];
			D[i][j] = INT_MAX;
		}
	}
	cin >> sx >> sy;
	cin >> ex >> ey;

	m = sx;
	n = sy;
	NODE n1 = { m, n, G[m][n] };
	q.push(n1);
	while (1) {
		NODE tmp = q.top();
		q.pop();
		m = tmp.lx;
		n = tmp.ly;
		D[m][n] = tmp.value;
		if ((tmp.lx == ex) && (tmp.ly == ey))
			break;

		res = count_node(tmp);
		if (res == 100) { //상하좌우 다 있는 경우
			if (D[m - 1][n] > D[m][n]) {
				NODE north = { m - 1, n, D[m][n] + G[m - 1][n] };
				q.push(north);
			}
			if (D[m][n - 1] > D[m][n]) {
				NODE west = { m, n - 1, D[m][n] + G[m][n - 1] };
				q.push(west);
			}
			if (D[m + 1][n] > D[m][n]) {
				NODE south = { m + 1, n, D[m][n] + G[m + 1][n] };
				q.push(south);
			}
			if (D[m][n + 1] > D[m][n]) {
				NODE east = { m, n + 1, D[m][n] + G[m][n + 1] };
				q.push(east);
			}
		}
		else if (res == 101) { //1행인경우
			if (D[m][n - 1] > D[m][n]) {
				NODE west = { m, n - 1, D[m][n] + G[m][n - 1] };
				q.push(west);
			}
			if (D[m + 1][n] > D[m][n]) {
				NODE south = { m + 1, n, D[m][n] + G[m + 1][n] };
				q.push(south);
			}
			if (D[m][n + 1] > D[m][n]) {
				NODE east = { m, n + 1, D[m][n] + G[m][n + 1] };
				q.push(east);
			}
		}
		else if (res == 110) { // 1열인경우
			if (D[m - 1][n] > D[m][n]) {
				NODE north = { m - 1, n, D[m][n] + G[m - 1][n] };
				q.push(north);
			}
			if (D[m + 1][n] > D[m][n]) {
				NODE south = { m + 1, n, D[m][n] + G[m + 1][n] };
				q.push(south);
			}
			if (D[m][n + 1] > D[m][n]) {
				NODE east = { m, n + 1, D[m][n] + G[m][n + 1] };
				q.push(east);
			}
		}
		else if (res == 111) { // 1행1열인경우
			if (D[m + 1][n] > D[m][n]) {
				NODE south = { m + 1, n, D[m][n] + G[m + 1][n] };
				q.push(south);
			}
			if (D[m][n + 1] > D[m][n]) {
				NODE east = { m, n + 1, D[m][n] + G[m][n + 1] };
				q.push(east);
			}
		}
	}
	cout << D[m][n];
	return 0;
}