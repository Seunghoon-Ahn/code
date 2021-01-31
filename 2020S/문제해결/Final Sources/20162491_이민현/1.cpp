#include<iostream>
using namespace std;

char arr[2188][2188];
int sum[3];

void dq(int n, int a, int b) {
	int first = arr[a][b];
	bool flag = true;
	if (n == 1) {
		if (arr[a][b] == -1) {
			sum[0]++;
		}
		else if (arr[a][b] == 0) {
			sum[1]++;
		}
		else {
			sum[2]++;
		}
		return;
	}
	for (int i = a; i < a + n; i++) {
		for (int j = b; j < b + n; j++) {
			if (first != arr[i][j]) {
				flag = false;
			}
		}
	}
	if (flag == false) {
		dq(n / 3, a, b);
		dq(n / 3, a, b + n / 3);
		dq(n / 3, a, b + n / 3 * 2);
		dq(n / 3, a + n / 3, b);
		dq(n / 3, a + n / 3, b + n / 3);
		dq(n / 3, a + n / 3, b + n / 3 * 2);
		dq(n / 3, a + n / 3 * 2, b);
		dq(n / 3, a + n / 3 * 2, b + n / 3);
		dq(n / 3, a + n / 3 * 2, b + n / 3 * 2);
	}
	else {
		if (arr[a][b] == -1) {
			sum[0]++;
		}
		else if (arr[a][b] == 0) {
			sum[1]++;
		}
		else {
			sum[2]++;
		}
	}
}

int main(void) {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	
	dq(n, 0, 0);

	for (int i = 0; i < 3; i++) {
		cout << sum[i] << endl;
	}
}