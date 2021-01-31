#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdlib>
#include<vector>

#define ZERO 0
#define ONE 1
#define MINUS 2

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int N;
vector<vector<int>> v;
int cnt[3];

bool isSame(int sz, int x, int y) {
	if (sz == 3)
	{
		int flag = true;
		for (int i = x; i < x + 3; ++i)
		{
			for (int j = y; j < y + 3; ++j)
			{
				if (v[i][j] != v[x][y])
				{
					flag = false;
					break;
				}
			}
			if (!flag)
				break;
		}
		return flag;
	}

	int newSZ = sz / 3;
	if (isSame(newSZ, x, y) && isSame(newSZ, x + newSZ, y) && isSame(newSZ, x + newSZ * 2, y)
		&& isSame(newSZ, x, y + newSZ) && isSame(newSZ, x + newSZ, y + newSZ) && isSame(newSZ, x + newSZ * 2, y + newSZ)
		&& isSame(newSZ, x, y + newSZ * 2) && isSame(newSZ, x + newSZ, y + newSZ * 2) && isSame(newSZ, x + newSZ * 2, y + newSZ * 2))
	{
		if (v[x][y] == v[x + newSZ][y] == v[x + newSZ * 2][y]
			== v[x][y + newSZ] == v[x + newSZ][y + newSZ] == v[x + newSZ * 2][y + newSZ]
			== v[x][y + newSZ * 2] == v[x + newSZ][y + newSZ * 2] == v[x + newSZ * 2][y + newSZ * 2])
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void solve(int sz, int x, int y)
{
	if (isSame(sz, x, y))
		++cnt[v[x][y]];
	else {
		if (sz == 3)
		{
			for (int i = x; i < x + 3; ++i)
			{
				for (int j = y; j < y + 3; ++j)
				{
					cnt[v[i][j]]++;
				}
			}
		}
		else {
			int newSZ = sz / 3;
			solve(newSZ, x, y); solve(newSZ, x + newSZ, y);  solve(newSZ, x + newSZ * 2, y);
			solve(newSZ, x, y + newSZ); solve(newSZ, x + newSZ, y + newSZ); solve(newSZ, x + newSZ * 2, y + newSZ);
			solve(newSZ, x, y + newSZ * 2); solve(newSZ, x + newSZ, y + newSZ * 2); solve(newSZ, x + newSZ * 2, y + newSZ * 2);
		}
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	v.resize(N);

	for (int i = 0; i < N; ++i)
		v[i].resize(N);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> v[i][j];
			if (v[i][j] == -1)
				v[i][j] = 2;
		}
	}

	if (N == 1)
		cnt[v[0][0]]++;
	else
		solve(N, 0, 0);

	cout << cnt[MINUS] << '\n' << cnt[ZERO] << '\n' << cnt[ONE] << '\n';

	return 0;
}

/**
9
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
0 1 -1 0 1 -1 0 1 -1
0 -1 1 0 1 -1 0 1 -1
0 1 -1 1 0 -1 0 1 -1

9
0 0 1 0 0 1 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 1 0 0 1 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 1 0 0 1 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0

3
1 1 1 
1 1 1
1 1 1
**/