#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> v;

int main(void) {
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) {
		int a;
		cin >> a;
		v.push_back(a);
	}

	sort(v.begin(), v.end());

	for(int i = 0; i < t; i++)
		cout << v[i] << '\n';
	
	return 0;
}

