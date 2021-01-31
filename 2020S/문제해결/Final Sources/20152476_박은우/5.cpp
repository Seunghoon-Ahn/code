#include <cstdio>
#include <vector>
using namespace std;

int n;
int s[21][21] = { 0, };
int diff = 10000000;
void dfs(int cur,int score1, int score2, vector<int> &team1, vector<int> &team2, int num1, int num2) {
	if (cur > n) return;
	if (num1 > n / 2 || num2 > n/2) return;
	if (num1 == num2 && num1 == n / 2) {
		if (score1 > score2) {
			if (diff > score1 - score2) {
				diff = score1 - score2;
			}
		}
		else {
			if (diff > score2 - score1) {
				diff = score2 - score1;
			}
		}
		return;
	}
	int plus1 = 0, plus2 = 0;
	for (int i = 0; i < team1.size(); i++) {
		plus1 += s[team1[i]][cur] + s[cur][team1[i]];
	}
	for (int i = 0; i < team2.size(); i++) {
		plus2 += s[team2[i]][cur] + s[cur][team2[i]];
	}
	team1.push_back(cur);
	dfs(cur + 1,score1+plus1, score2, team1, team2, num1 + 1, num2);
	team1.pop_back();
	team2.push_back(cur);
	dfs(cur + 1, score1, score2 + plus2, team1, team2, num1, num2 + 1);
	team2.pop_back();
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &s[i][j]);
		}
	}
	vector<int> team1, team2;
	dfs(0, 0, 0, team1, team2, 0, 0);
	printf("%d", diff);
	return 0;
}