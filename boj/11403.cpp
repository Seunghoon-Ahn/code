#include <bits/stdc++.h>
using namespace std;
int mmap[102][102];
int n;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> mmap[i][j];
	for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(mmap[i][j])
					continue;
				if(k == i || k == j)
					continue;
				if(mmap[i][k] && mmap[k][j])
					mmap[i][j] = 1;
			}
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << mmap[i][j] << ' ';
		cout << '\n';
	}
	return 0;
}
