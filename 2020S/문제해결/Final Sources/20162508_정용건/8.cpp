#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

#define NMAX 100
#define MMAX 5000

using namespace std;
int n, m, res;
int match[NMAX];//match[i] : i번째 노트북에 매칭된 사람
bool isVis[NMAX];//방문여부
vector<int>v[NMAX];

bool dfs(int loc) {
	//cout << loc << endl;
	if (isVis[loc])
		return false;
	isVis[loc] = true;
	for (int target : v[loc]) {
		if (match[target] == -1) {//만약 해당 노트북과 매칭된 사람이 없으면
			match[target] = loc;//매칭시켜줌
			res++;//매칭횟수증가
			return true;
		}
	}
	for (int target : v[loc]) {
		if (match[target] != -1 
			&& dfs(match[target])) {//만약 해당 노트북이 다른 사람과 매칭 가능하면
			match[target] = loc;//뺏어옴, 횟수는 증가시키지 않음
			return true;
		}
	}
	return false;
}

void matching() {
	fill(match, match + n, -1);
	for (int i = 0; i < n; i++) {
		fill(isVis, isVis + n, false);
		dfs(i);
	}
	return;
}

int main() {
	int a, b, temp;
	cin >> n >> m;
	temp = m;
	while (temp--) {
		cin >> a >> b;
		--a; --b;//1부터 시작하는거 0부터로 맞춰줌
		v[a].push_back(b);//a에서 b로가는 edge
	}
	matching();
	cout << res << endl;
	return 0;
}