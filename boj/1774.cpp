#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pp;
typedef struct {
	int v1, v2;
	double w;
}edge;
vector <pp> point;
vector <edge> route;
int N, M;
int par[1010];
int rnk[1010];

void init(int n) {
	for(int i = 0; i < n; i++) {
		par[i] = i;
		rnk[i] = 1;
	}
}

int find(int x) {
	if(par[x] == x)
		return x;
	return par[x] = find(par[x]);
}

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return;
	if(rnk[x] > rnk[y])
		swap(x, y);
	par[x] = y;
	if(rnk[x] == rnk[y])
		rnk[y]++;
}

double calcul(pp a, pp b) {
	double res = sqrt(pow(abs(b.first - a.first), 2) + pow(abs(b.second - a.second), 2));
	return res;
}

bool cmp(edge a, edge b) {
	return a.w < b.w;
}

int main(void) {
	int tmp1, tmp2;
	double res = 0;
	cin >> N >> M;
	init(N);
	point.push_back({-1, -1});
	for(int i = 0; i < N; i++) {
		cin >> tmp1 >> tmp2;
		point.push_back({tmp1, tmp2});
	}
	for(int i = 0; i < M; i++) {
		cin >> tmp1 >> tmp2;
		unite(tmp1, tmp2);
	}
	for(int i = 1; i <= N; i++) {
		for(int j = i+1; j <= N; j++) {
			double dist = calcul(point[i], point[j]);
			edge tmpedge;
			tmpedge.v1 = i;
			tmpedge.v2 = j;
			tmpedge.w = dist;
			route.push_back(tmpedge);
		}
	}
	sort(route.begin(), route.end(), cmp);

	for(int i = 0; i < route.size(); i++) {
		if(find(route[i].v1) != find(route[i].v2)) {
			unite(route[i].v1, route[i].v2);
			res += route[i].w;
		}
	}
	printf("%.2lf\n", res);
	return 0;
}

