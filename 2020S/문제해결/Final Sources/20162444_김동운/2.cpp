#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MN = 100101;
int N, M;
int t[MN];

long long f(int time) {
	long long ret = 0;
	for (int i = 0; i < N; i++)
		ret += time / t[i];
	return ret;
}

int main(void)
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) 
		cin >> t[i];
	
	int lo = 0, hi = 1e9;
	for (int i = 0; i < 60; i++) {
		int mid = (lo + hi) / 2;
		if (f(mid) >= M)
			hi = mid;
		else
			lo = mid;
	}
	cout << hi;
}