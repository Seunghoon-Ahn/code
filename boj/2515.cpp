#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pp;
pp pic[300002];
int dp[300002];
int lenmax[300002];
int N, S;

bool cmp(pp a, pp b) {
	if(a.first == b.first)
		return a.second > b.second;

	return a.first < b.first;
}

int bsearch(int num) {
	int lo = 0, hi = num - 1;

	while(1) {
		if(lo > hi)
			break;
		int mid = (lo + hi) / 2;
		if(pic[num].first - pic[mid].first >= S)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return hi;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> S;

	pic[0].first = pic[0].second = 0;

	for(int i = 1; i <= N; i++)
		cin >> pic[i].first >> pic[i].second;
	
	sort(pic, pic + N + 1, cmp);
	
	for(int i = 1; i <= N; i++) {
		if(pic[i].first - lenmax[i-1] >= S) {
			dp[i] = dp[i-1] + pic[i].second;
			lenmax[i] = pic[i].first;
		}
		else {
			int bef = bsearch(i);

			if(dp[i-1] > dp[bef] + pic[i].second) {
				dp[i] = dp[i-1];
				lenmax[i] = lenmax[i-1];
			}
			else {
				dp[i] = dp[bef] + pic[i].second;
				lenmax[i] = pic[i].first;
			}
		}
	}
	cout << dp[N] << '\n';
	return 0;
}	
