#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<pair<int, int>> v;

int main(void) {
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) {
		int a, b;
		cin >> a >> b;
		v.push_back({a, b});
	}

	sort(v.begin(), v.end());

	for(int i = 0; i < t; i++) {
		cout << v[i].first << ' ' << v[i].second << '\n';
	}

	return 0;
}

