#include <iostream>
#include <algorithm>
#include <cstdbool>
#include <vector>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	if(a.second == b.second)
		return a.first < b.first;
	else
		return a.second < b.second;
}


vector<pair<int, int>> v;

int main(void) {
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) {
		int a, b;
		cin >> a >> b;
		v.push_back({a, b});
	}

	sort(v.begin(), v.end(), cmp);

	for(int i = 0; i < t; i++) {
		cout << v[i].first << ' ' << v[i].second << '\n';
	}

	return 0;
}

