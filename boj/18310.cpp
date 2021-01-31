#include <bits/stdc++.h>
using namespace std;
int n;
vector <int> v;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	int tmp;
	for(int i = 0; i < n; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	sort(v.begin(), v.end());
	cout << v[(n-1) / 2] << '\n';
	return 0;
}

