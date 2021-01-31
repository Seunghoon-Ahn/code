#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int N, M, Q;
vector <pair<int, int>> link; //연결 저장
vector <int> d; //삭제할 링크 저장
bool checklink[100101]; //삭제 안되는 연결 확인용
long long buddy[100101];
int par[100101];
long long res = 0;
vector <int> g[100101];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		buddy[i] = 1;
	}
}

int find(int x) {
	if (par[x] == x)
		return x;
	return par[x] = find(par[x]);
}

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		g[x].push_back(y);
		g[y].push_back(x);

		if (x < y)
			swap(x, y);
		par[x] = y;
		buddy[y] += buddy[x];
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> Q;
	int tmp1, tmp2;
	link.push_back({ 0, 0 });
	init(N);
	for (int i = 1; i <= M; i++) {
		cin >> tmp1 >> tmp2;
		link.push_back({ tmp1, tmp2 });
		checklink[i] = true;
	}
	for (int i = 1; i <= Q; i++) {
		cin >> tmp1;
		d.push_back(tmp1);
		checklink[tmp1] = false;
	}

	for (int i = 1; i <= M; i++)
		if (checklink[i] == true)
			unite(link[i].first, link[i].second);

	reverse(d.begin(), d.end());

	for (auto tmp : d) {
		if (find(link[tmp].first) != find(link[tmp].second)) {
			long long t1 = buddy[find(link[tmp].first)];
			long long t2 = buddy[find(link[tmp].second)];
			res += (t1 * t2);
		}
		unite(link[tmp].first, link[tmp].second);
	}
	cout << res << '\n';
	return 0;
}
