#include <iostream>
#include <functional>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

typedef struct node {
	int lx;
	int ly;
	int distance;
	int bound;
}NODE;

bool operator < (node t, node u) {
	return t.bound > u.bound;
}
priority_queue< node > q;

NODE N[11];
int Field[21][21];
//bool Bcheck[11] = { 0 };

int main(void) {
	int fieldx, fieldy;
	int sx, sy;
	int nodecnt;
	int i = 1;
	int tmp1, tmp2;
	int res = 0;

	cin >> fieldx >> fieldy;
	cin >> sx >> sy;
	cin >> nodecnt; // 점의 갯수 (시작점 제외)
	N[0] = NODE{ sx, sy, 0 , 0 };
	while (i <= nodecnt) {
		cin >> tmp1 >> tmp2;
		N[i] = NODE{ tmp1, tmp2, 0,  INT_MAX };
		i++;
	}

	i = 1;
	while (i <= nodecnt) {   // 시작점에서 다른 점으로의 bound를 계산해서 큐에 넣음
		N[i].bound = abs(N[i].lx - sx) + abs(N[i].ly - sy);
		q.push(N[i]);
		i++;
	}
	bool Bcheck[11] = { 0 };
	i = 1;
	int lastnum = 0;
	while (i <= nodecnt) {
		int nodenum;
		int checknum = 0;

		NODE point = q.top();
		q.pop();
		for (int i = 1; i <= nodenum; i++) {
			if (point.lx == N[i].lx && point.ly == N[i].ly)
				nodenum = i;
		}
		//if (nodenum == 0) {
			for (int i = 1; i <= nodecnt; i++)
				if (Bcheck[i] == false)
					checknum++;
			if (!checknum) {
				lastnum = i;
				res = N[nodenum].bound;
				break;
			}
		//}
	}
	return 0;
}
