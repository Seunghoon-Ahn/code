// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;

int n;
int res = -1;

vector<int> v;
int map[22][22];

int main() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		v.push_back(i);
	}

	bool twice = false;
	do {
		if (twice) {
			twice = false;
			continue;
		}
		twice = true;

		int start = 0;
		int link = 0;

		for (int i = 1; i <= (n / 2)-1; i++) {
			for (int j = i + 1; j <= n / 2; j++) {
				start += map[v[i-1]][v[j-1]] + map[v[j-1]][v[i-1]];
			}
		}
		for (int i = 1+n/2; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				link += map[v[i-1]][v[j-1]] + map[v[j-1]][v[i-1]];
			}
		}

		int temp = abs(start - link);

		if (res == -1 || res > temp) res = temp;

	} while (next_permutation(v.begin(), v.end()));


	cout << res;
	return 0;
}