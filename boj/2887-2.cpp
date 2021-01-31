#include <bits/stdc++.h>
using namespace std;
typedef struct {
	int x, y, z;
}planet;
typedef struct {
	int v1, v2, w;
}edge;
vector <planet> vec;
vector <edge> tunnel;
int N;
int par[101010];
int rnk[101010];

void init(int x) {
	for(int i = 0; i < x; i++) {
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
	if(x == y)
		return;
	if(rnk[x] > rnk[y])
		swap(x, y);
	par[x] = y;
	if(rnk[x] == rnk[y])
		rnk[y]++;
}

int calcul (planet a, planet b) {
	int res = min(abs(a.x - b.x), min(abs(a.y - b.y), abs(a.z - b.z)));
	return res;
}

bool cmp(edge a, edge b) {
	return a.w < b.w;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int res = 0;
	cin >> N;
	init(N);
	planet tmpp;
	for(int i = 0; i < N; i++) {
		cin >> tmpp.x >> tmpp.y >> tmpp.z;
		vec.push_back(tmpp);
	}
	for(int i = 0; i < N; i++) {
		for(int j = i+1; j < N; j++) {
			int dist = calcul(vec[i], vec[j]);
			edge tmpe;
			tmpe.v1 = i;
			tmpe.v2 = j;
			tmpe.w = dist;
			tunnel.push_back(tmpe);
		}
	}
	sort(tunnel.begin(), tunnel.end(), cmp);

	for(int i = 0; i < tunnel.size(); i++) {
		if(find(tunnel[i].v1) != find(tunnel[i].v2)) {
			unite(tunnel[i].v1, tunnel[i].v2);
			res += tunnel[i].w;
		}
	}
	cout << res << '\n';
	return 0;
}


	

