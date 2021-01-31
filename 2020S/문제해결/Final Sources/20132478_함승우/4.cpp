#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX = 1005;

vector < pair <int, int> > p[MAX];

int visited[MAX][MAX] = { 0 };
int dp[MAX][MAX] = { 0 };

int find_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int N, M, K;

int main()
{
	int size;
	int from, to, cost;
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		size = 0;
		cin >> from >> to >> cost;
		if (from < to) {
			if (visited[from][to] > 0) {	//경로 겹침
				int change = find_max(visited[from][to], cost);
				visited[from][to] = change;
			}
			else {
				p[from].push_back({ to, cost });
				visited[from][to] = cost;
			}
		}
	}

	for (int diag = 1; diag <= N+1; diag++) {	//대각선 진행 횟수
		for (int i = 1; i <= N - diag; i++) {
			if (diag == 1) {
				dp[i][i + 1] = visited[i][i + 1];
				continue;
			}

			int MX = visited[i][diag + i];

			for (int cur = 1; cur <= diag-1; cur++) {
				MX = find_max(dp[i][i+cur] + dp[i + cur][diag + i] , MX);
			}

			dp[i][diag+i] = MX;
		}
	}

	cout << dp[1][N];
}
