#include <bits/stdc++.h>
using namespace std;
int T;
int par[100003];
vector <int> v1, v2;
int st, en;
void find1(int num) {
	int tmp = num;
	while(1) {
		int parent = par[tmp];
		v1.push_back(tmp);
		if(parent == 0)
			break;
		else
			tmp = parent;
	}
}

void find2(int num) {
	int tmp = num;
	while(1) {
		int parent = par[tmp];
		v2.push_back(tmp);
		if(parent == 0)
			break;
		else
			tmp = parent;
	}
}

int search(void) {
	for(auto next : v2) {
		for(int i = 0; i < v1.size(); i++)
			if(next == v1[i])
				return next;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	while(T--) {
		int N;
		int tmp1, tmp2;
		v1.clear();
		v2.clear();
		memset(par, 0, sizeof(par));

		cin >> N;
		for(int i = 0; i < N - 1; i++) {
			cin >> tmp1 >> tmp2;
			par[tmp2] = tmp1;
		}
		cin >> st >> en;
		find1(st);
		find2(en);
		int res = search();
		cout << res << '\n';
	}
	return 0;
}
