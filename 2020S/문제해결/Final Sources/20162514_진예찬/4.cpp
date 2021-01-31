#include <stdio.h>
#include <vector>
#define N 300
#define INF 2123465789

using namespace std;
typedef pair<int, int> pi;

vector<pi> e[N + 5];
int di[N + 5];
int n, m, k;
int max = 0;
int dfs(int v, int w) {
	if (v == n) {
		return w;
	}
	int &val = di[v];
	for (pi t : e[v]) {
		int temp = dfs(t.first, w + t.second);
		if (val < temp)
			val = temp;
	}
	return val;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	int s, t, w;
	for (int i = 0; i < k; i++) {
		scanf("%d%d%d", &s, &t, &w);
		if (s > t)
			continue;

		e[s].push_back({ t,w });
	}
	printf("%d", dfs(1,0));
}