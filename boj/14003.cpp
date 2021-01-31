#include <bits/stdc++.h>
using namespace std;
int n;
int arr[1010101];
int idx[1010101];
vector<int> dp;
vector<int> res;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	dp.push_back(-1000000001);

	for(int i = 0; i < n; i++) {
		if(dp.back() < arr[i]) {
			dp.push_back(arr[i]);
			idx[i] = dp.size() - 1;
		}
		else {
			auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
			*it = arr[i];
			idx[i] = it - dp.begin();
		}
	}

	int len = dp.size() - 1;
	cout << len << '\n';

	for(int i = n - 1; i >= 0; i--) {
		if(idx[i] == len) {
			res.push_back(arr[i]);
			len--;
		}
	}
	len = dp.size() - 1;
	for(int i = len - 1; i >= 0; i--)
		cout << res[i] << ' ';

	return 0;
}


	
