#include <bits/stdc++.h>

using namespace std;
vector <int> v;
int n, m;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	int tmp;
	for(int i = 0; i < n; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	sort(v.begin(), v.end());
	cin >> m;
	for(int i = 0; i < m; i++) {
		cin >> tmp;
		int res = binary_search(v.begin(), v.end(), tmp);
		if(res)
			cout << 1 << '\n';
		else
			cout << 0 << '\n';
	}
	return 0;
}

