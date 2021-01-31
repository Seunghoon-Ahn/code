#include <bits/stdc++.h>
using namespace std;
int T;
long long arr[102];
int main(void) {
	cin >> T;
	arr[1] = arr[2] = arr[3] = 1;
	for(int i = 4; i <= 100; i++)
		arr[i] = arr[i-2] + arr[i-3];
	while(T--) {
		int tmp;
		cin >> tmp;
		cout << arr[tmp] << '\n';
	}
	return 0;
}
