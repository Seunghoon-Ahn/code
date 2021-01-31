#include <bits/stdc++.h>
using namespace std;
int N, Q;
int arr[1010101];
int res[1010101];
int sav = 0;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tmp1, tmp2;
	cin >> N >> Q;
	for(int i = 1; i <= N; i++) {
		cin >> arr[i];
		res[i] = res[i-1] ^ arr[i];
	}
	for(int i = 1; i <= Q; i++) {
		cin >> tmp1 >> tmp2;
		sav = sav ^ (res[tmp2] ^ res[tmp1-1]);
	}
	cout << sav << '\n';
	return 0;
}
		
