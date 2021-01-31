#include <bits/stdc++.h>
using namespace std;
int N, M;
int par[101010];
int rnk[101010];
typedef struct {
	int v1, v2;
	int w;
}edge;
edge arr[1010101];

void init(int n) {
	for(int i = 0; i < N; i++) {
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
	if(rnk[x] == rnk[y])
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
	cin >> N >> M;
	init(N);
	for(int i = 0; i < M; i++)
		cin >> arr[i].v1 >> arr[i].v2 >> arr[i].w;
	sort(arr, arr + M, cmp);
	
	int res = 0;
	int mmax = 0;
	for(int i = 0; i < M; i++) {
		if(find(arr[i].v1) != find(arr[i].v2)) {
			unite(arr[i].v1, arr[i].v2);
			res += arr[i].w;
			if(arr[i].w > mmax)
				mmax = arr[i].w;
		}
	}
	cout << res - mmax << '\n';
	return 0;
}

