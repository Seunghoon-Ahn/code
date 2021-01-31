#include <bits/stdc++.h>
using namespace std;
int N;
vector <int> dp;
int arr[1000001];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for(int i = 0; i < N; i++)
		cin >> arr[i];
	dp.push_back(-1000001);
	for(int i = 0; i < N; i++) {
		if(dp.back() < arr[i])
			dp.push_back(arr[i]);
		else {
			auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
			*it = arr[i];
		}
	}

	cout << dp.size() - 1;
	return 0;
}
