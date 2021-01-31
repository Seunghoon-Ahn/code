#include <iostream>
#include <algorithm>
#include <cstdio>
#define MAX 100000
using namespace std;

int N; //점 개수
int point[101]; //처음 점 저장
int dp[102][102]; //dp
int divide[102][102]; //중간 연결점
int h[102][102]; //높이 저장
int pushcnt = 0;

bool count_point(int start, int end) {
	int num1 = 0;
	int num0 = 0;
	if (start == end || end - start == 1) return true;
	for (int i = start; i <= end; i++) {
		if (point[i] == 0) num0++;
		else num1++;
	}
	if (num1 == num0) return true;
	return false;
}

void make_dp(int start, int finish) {
	if (start > finish) dp[start][finish] = 0;
	if (dp[start][finish] == MAX) {
		for (int loc = start + 1; loc <= finish; loc += 2) {
			if ((point[start] != point[loc]) && count_point(start, loc)) {
				make_dp(start + 1, loc - 1);
				make_dp(loc + 1, finish);
				int gap = loc - start;
				if (dp[start][finish] > dp[start + 1][loc - 1] + dp[loc + 1][finish] + gap + 2 * (h[start + 1][loc - 1] + 1)) {
					dp[start][finish] = dp[start + 1][loc - 1] + dp[loc + 1][finish] + gap + 2 * (h[start + 1][loc - 1] + 1);
					h[start][finish] = max(h[start + 1][loc - 1] + 1, h[loc + 1][finish]);
					divide[start][finish] = loc;
				}
			}
		}
	}
}

void point_push(int s, int e) {
	if (s > e) return;
	int tmp = divide[s][e];
	printf("%d %d\n", s, tmp);
	point_push(s+1, tmp-1);
	point_push(tmp+1, e);
}

int main(void) {
	char tmp;

	cin >> N;
	cin.ignore();

	for (int i = 1; i <= N; i++) {
		scanf("%c", &tmp);
		point[i] = tmp - '0';
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			dp[i][j] = MAX;
			h[i][j] = 0;
		}

	make_dp(1, N);

	cout << dp[1][N] <<'\n';

	point_push(1, N);

	return 0;
}