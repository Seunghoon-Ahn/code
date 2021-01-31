#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#pragma warning(disable:4996)
#define MAX 2190

using namespace std;

bool checkSame(pair<int,int> left_top, pair<int,int> right_down);
void cutPaper(pair<int, int> left_top, pair<int, int> right_down);

int paper[MAX][MAX];//20MB정도
int N;
int num[3];//0번 방부터 차례로 -1,0,1 종이의 개수

int main() {
	num[0] = 0; num[1] = 0; num[2] = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &paper[i][j]);
		}
	}

	cutPaper(make_pair(1, 1), make_pair(N, N));

	printf("%d\n%d\n%d\n", num[0], num[1], num[2]);
	return 0;
}
void cutPaper(pair<int, int> left_top, pair<int, int> right_down) {
	if (checkSame(left_top, right_down)) {//모두 같은 수 일때
		num[paper[left_top.first][left_top.second]+1]++;
		return;
	}
	//쪼개서 각각 cutPaper호출

	int gap = (right_down.first - left_top.first + 1) / 3;
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			pair<int, int> l_t, r_d;
			l_t.first = left_top.first + gap*i;
			l_t.second = left_top.second + gap*j;
			r_d.first = l_t.first + (gap-1);
			r_d.second = l_t.second + (gap-1);
			cutPaper(l_t, r_d);
		}
	}

}


bool checkSame(pair<int,int> left_top, pair<int,int> right_down) {
	//first에는 x좌표, second에는 y좌표

	int chk = paper[left_top.first][left_top.second];
	for (int i = left_top.first; i <= right_down.first; i++) {
		for (int j = left_top.second; j <= right_down.second; j++) {
			if (paper[i][j] != chk) return false;
		}
	}
	return true;
}