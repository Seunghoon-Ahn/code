#include <bits/stdc++.h>
using namespace std;
int arr[100001];
int N, M;

int main(void) {
	cin >> N >> M;
	for(int i = 0; i < N; i++)
		cin >> arr[i];

	sort(arr, arr+N);
	int max = 2000000004;
	int gap;
	for(int i = 0; i < N; i++) {
		int index = lower_bound(arr, arr + N, arr[i] + M) - arr;

		gap = arr[index] - arr[i];
		if(gap < max && index < N)
			max = gap;
	}
	cout << max << '\n';
	return 0;
}
