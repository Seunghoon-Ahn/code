#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;
const int MN = 101;
const int MM = 100101;
struct planet {
	int x, y, z,idx;
	int distance(const planet& p) {
		return min({ abs(x - p.x), abs(y - p.y), abs(z - p.z) });
	}
};
struct edge {
	int u, v, w;
};
int par[MN], rnk[MN];
void init(int n)
{
	for (int i = 1; i <= n; i++)
		par[i] = i, rnk[i] = 1;
}
int find(int x)
{
	if (par[x] == x)
		return x;
	return par[x] = find(par[x]);
}
void unite(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)
		return;
	if (rnk[x] > rnk[y])
		swap(x, y);
	par[x] = y;
	if (rnk[x] == rnk[y])
		rnk[y]++;
}
bool cmp(edge a, edge b) {
	return a.w < b.w;
}
bool cmpX(planet &a, planet &b) {
	return a.x < b.x;
}
bool cmpY(planet &a, planet &b) {
	return a.y < b.y;
}
bool cmpZ(planet &a, planet &b) {
	return a.z< b.z;
}
int main(void) {
	ios::sync_with_stdio(false);    cin.tie(NULL);
	int N;   cin >> N;
	init(N);
	vector<planet> pos(N);
	for (int i = 0; i < N; i++) {
		cin >> pos[i].x >> pos[i].y >> pos[i].z;
		pos[i].idx = i;
	}

	vector<edge> arr;
	sort(pos.begin(), pos.end(), cmpX);
	for (int i = 1; i < N; i++) {
		arr.push_back({ pos[i - 1].idx , pos[i].idx, pos[i - 1].distance(pos[i]) });
	}
	sort(pos.begin(), pos.end(), cmpY);
	for (int i = 1; i < N; i++) {
		arr.push_back({ pos[i - 1].idx , pos[i].idx, pos[i - 1].distance(pos[i]) });
	}
	sort(pos.begin(), pos.end(), cmpZ);
	for (int i = 1; i < N; i++) {
		arr.push_back({ pos[i - 1].idx , pos[i].idx, pos[i - 1].distance(pos[i]) });
	}
	sort(arr.begin(), arr.end(),cmp);

	long long res = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (find(arr[i].u) != find(arr[i].v)) {
			unite(arr[i].u, arr[i].v);
			res += arr[i].w;
		}
	}
	printf("%lld\n", res);
	return 0;
}
