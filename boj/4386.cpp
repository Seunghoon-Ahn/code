#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> pd;
typedef struct {
	int v1, v2;
	double w;
}edge;
vector <pd> star;
int n;
int par[103];
int rnk[103];
vector <edge> route;

void init(int x) {
	for(int i = 1; i <= x; i++) {
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

double calcul(pd a, pd b) {
	double res = sqrt(pow(abs(b.first - a.first), 2) + pow(abs(b.second - a.second), 2));
	return res;
}

bool cmp(edge a, edge b) {
	return a.w < b.w;
}

int main(void) {
	double tmp1, tmp2;
	double res = 0;
	cin >> n;
	init(n);
	star.push_back({-1.0, -1.0});
	for(int i = 0; i < n; i++) {
		cin >> tmp1 >> tmp2;
		star.push_back({tmp1, tmp2});
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			double dist = calcul(star[i], star[j]);
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


