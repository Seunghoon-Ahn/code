#include <bits/stdc++.h>

using namespace std;
const int MN = 200;
int N;
vector <int> g[MN];
int value[MN][MN];
int f[MN][MN];

int count_totalflow(void) {
	queue<int> q;
	int total = 0;
	while (1) {
		int arr[MN];
		bool visit[MN];
		memset(visit, 0, sizeof(visit));
		memset(arr, 0, sizeof(arr));
		visit['A'] = true;
		q.push('A');

		while (!q.empty()) {
			int curloc = q.front();
			q.pop();
			for (int i = 0; i < g[curloc].size(); i++) {
				if (!visit[g[curloc][i]] && value[curloc][g[curloc][i]] - f[curloc][g[curloc][i]] > 0) {
					visit[g[curloc][i]] = true;
					arr[g[curloc][i]] = curloc;
					q.push(g[curloc][i]);
				}
			}
		}
		if (visit['Z'] == 0)
			break;
		int mmax = INT_MAX;
		for (int i = 'Z'; i != 'A'; i = arr[i])
			mmax = min(mmax, value[arr[i]][i] - f[arr[i]][i]);
		for (int i = 'Z'; i != 'A'; i = arr[i]) {
			f[arr[i]][i] += mmax;
			f[i][arr[i]] -= mmax;
		}
		total += mmax;
	}
	return total;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	char tmp1, tmp2;
	int tmp3;
	for (int i = 1; i <= N; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		g[tmp1].push_back(tmp2);
		g[tmp2].push_back(tmp1);
		value[tmp1][tmp2] += tmp3;
		value[tmp2][tmp1] += tmp3;
	}
	int res = count_totalflow();
	cout << res << '\n';
	return 0;
}
