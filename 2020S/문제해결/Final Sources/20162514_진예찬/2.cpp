#include <stdio.h>
#include <vector>
#include <algorithm>
#define M 1000000000
#define N 100000
using namespace std;
typedef long long ll;
int n, m;
int time[N + 5];
int late = 0;
int res = 0;
bool det(int tar) {
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		int temp = tar  / time[i];
		ans += temp;
	}
	return ans >= m;
}
void par(int s, int e) {
	int mid = (s + e) / 2;
	if (s > e) {
		res = s;
		return;
	}
	if (det(mid)) {
		res = mid;
		par(s, mid-1);
	}
	else {
		par(mid + 1, e);
	}
}
int main() {
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &time[i]);
		if (time[i] > late)
			late = time[i];
	}
	sort(time + 1, time + 1 + n);
	par(1, M);
	printf("%d", res);
}