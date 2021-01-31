#include <bits/stdc++.h>
using namespace std;
int V, E;
typedef struct {
	int v1, v2;
	int w;
}edge;
int par[10101];
int rnk[10101];
edge arr[101010];

void init(int n) {
	for(int i = 1; i <= n; i++) {
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

bool cmp(edge a, edge b) {
	return a.w < b.w;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp1, tmp2, tmp3;
	cin >> V >> E;
	for(int i = 0; i < E; i++)
		cin >> arr[i].v1 >> arr[i].v2 >> arr[i].w;
	
	sort(arr, arr + E, cmp);

	int res = 0;
	for(int i = 0;i < E; i++) {
		if(find(arr[i].v1) != find(arr[i].v2)) {
			unite(arr[i].v1, arr[i].v2);
			res += arr[i].w;
		}
	}
	cout << res;
	return 0;
}

