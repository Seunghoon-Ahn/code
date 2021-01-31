#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;
vector <int> p[102]; //그 사람이 가능한 노트북
int maxmatch = 0;

int visit[102];

void solve(int person, int cur);

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);
	memset(visit, 0, sizeof(visit));
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		p[tmp1].push_back(tmp2);
	}
	solve(1, 0);

	cout << maxmatch;

	return 0;
}

void solve(int person, int cur) {
	if (person > N) {
		if (maxmatch < cur)
			maxmatch = cur;
		return;
	}
	int checksum = 0;

	for (int j = 0; j < p[person].size(); j++) {
		if(visit[p[person][j]] == 0) {
			checksum = 1;
			visit[p[person][j]] = 1;
			solve(person + 1, cur + 1);
			visit[p[person][j]] = 0;
		}
	}
	if (!checksum)
		solve(person + 1, cur);

	return;
}