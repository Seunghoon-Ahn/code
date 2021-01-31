#include <bits/stdc++.h>

using namespace std;

int main(void) {
	int tc;
	cin >> tc;

	for(int i = 0; i < tc; i++) {
		int arr[100002];
		int d, sd;
		cin >> d;
		sd = d;
		memset(arr, 0, sizeof(arr));

		for(int a = 2; a * a <= d; a++) {
			while(d % a == 0) {
				(arr[a])++;
				d /= a;
			}
		}
		if(d != 1)
			(arr[d])++;
		
		for(int k = 2; k <= sd; k++) {
			if(arr[k] != 0)
				cout << k << ' ' << arr[k] << '\n';
		}
	}

	return 0;
}

				
