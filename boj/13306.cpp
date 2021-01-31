#include <bits/stdc++.h>
using namespace std;
const int MN = 200101;

struct Query{
	int x, b, c, d;
};
int p[MN];
vector <Query> ques;
vector <bool> res;
int par[MN];
void init(int n) {
	for(int i = 1; i <= n; i++)
		par[i] = i;
}

int find(int x) {
	if(par[x] == x)
		return x;
	return par[x] = find(par[x]);
}

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	par[y] = x;
}

int main(void) {
	int N, Q;
	cin >> N >> Q;
	for(int i = 1; i <= N-1; i++)
		cin >> p[i+1];
	int q = N - 1 + Q;
	init(N);
	while(q--) {
		int x;
		cin >> x;
		if(x) {
			int c, d;
			cin >> c >> d;
			ques.push_back({x, 0, c, d});
		}
		else {
			int b;
			cin >> b;
			ques.push_back({x, b, 0, 0});
		}
	}
	reverse(ques.begin(), ques.end());

	for(auto tmp : ques) {
		if(tmp.x) {
			if(find(tmp.c) != find(tmp.d))
				res.push_back(false);
			else
				res.push_back(true);
		}
		else
			unite(tmp.b, p[tmp.b]);
	}
	for(int i = res.size() - 1; i >= 0; i--) {
		if(res[i])
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}

