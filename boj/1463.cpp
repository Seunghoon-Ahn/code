#include <bits/stdc++.h>
using namespace std;
int arr[1000001];
int main(void) {
	int n;
	cin >> n;
	arr[1] = 0;

	for(int i = 2; i <= n; i++) {
		if(i % 6 == 0)
			arr[i] = min(arr[i-1], min(arr[i/2], arr[i/3])) + 1;
		else if(i % 2 == 0)
			arr[i] = min(arr[i-1], arr[i/2]) + 1;
		else if(i % 3 == 0)
			arr[i] = min(arr[i-1], arr[i/3]) + 1;
		else
			arr[i] = arr[i-1] + 1;
	}
	cout << arr[n];
	return 0;
}
