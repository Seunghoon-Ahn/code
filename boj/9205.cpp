#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int t, n;
typedef pair<int, int> pp;
vector <pp> mart;
bool visit[104];
int nx, ny;
int ex, ey;
int check = 0;

void dfs(int a, int b) {
	int dist = abs(ex - a) + abs(ey - b);
	if(check == 1 || dist <= 1000) {
		check = 1;
		return;
	}
	for(int i = 0; i < mart.size(); i++) {
		if(visit[i])
			continue;
		dist = abs(mart[i].first - a) + abs(mart[i].second - b);
		if(dist > 1000)
			continue;
		else {
			visit[i] = true;
			dfs(mart[i].first, mart[i].second);
		}
	}
	
}


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while(t--) {
		cin >> n;
		cin >> nx >> ny;
		mart.clear();
		memset(visit, 0, sizeof(visit));

		for(int i = 0; i < n; ++i) {
			int tmp1, tmp2;
			cin >> tmp1 >> tmp2;
			mart.push_back({tmp1, tmp2});
		}
		cin >> ex >> ey;
		check = 0;
		dfs(nx, ny);

		if(check == 1)
			cout << "heppy" << '\n';
		else
			cout << "sad" << '\n';
	}
	return 0;
}

