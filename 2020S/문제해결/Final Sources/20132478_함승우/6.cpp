#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

const int MAX = 105;

int cheese[MAX][MAX];

int n, m;
int cnt = 0;
int result = 0;

vector < pair <int, int> > v;

void dfs(int i, int j);

int dive(int i, int j);

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> cheese[i][j];
			cnt++;
		}
	}
	while (cnt > 0) {
		v.clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				dfs(i, j);
			}
		}
		result++;
		
		int size = v.size();
		for (int i = 0; i < size; i++) {
			int a = v[i].first;
			int b = v[i].second;
			cheese[a][b] = 0;
		}
	}

	printf("%d", result);
}

void dfs(int i, int j)
{
	if (cheese[i][j] == 1) {
		dive(i, j);
	}
}

int dive(int i, int j)
{
	if (i<0 || i>n || j<0 || j>m)
		return 0;
	int check = 0;

	if (cheese[i + 1][j] == 0)
		check += dive(i + 1, j);
	if (cheese[i][j - 1] == 0)
		check += dive(i, j - 1);
	if (cheese[i][j + 1] == 0)
		check += dive(i, j + 1);
	if (cheese[i - 1][j] == 0)
		check += dive(i - 1, j);

	if (check >= 2) {
		cnt--;
		v.push_back({ i,j });
	}
}