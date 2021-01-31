#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int money[100010] = { 0 };
int N, M;  //N 날짜 수 M 인출 수
int total;
int cur_k;
int maxmoney = 0;

void parametric(int x, int y) {
	int mid = (x + y) / 2;
	int cnt = 1;
	int curmoneyleft = mid;

	if ( x == y ) {
		cur_k = mid;
		return;
	}

	for (int i = 1; i <= N; i++) {
		if ((curmoneyleft - money[i]) >= 0) {
			curmoneyleft -= money[i];
			continue;
		}
		else {
			curmoneyleft = mid;
			curmoneyleft -= money[i];
			cnt++;
		}
	}
	if (cnt <= M)
		parametric(x, mid);
	else
		parametric(mid + 1, y);
}

int main(void) {

	cin >> N >> M;
	int i= 1;
	
	while (i <= N) {
		cin >> money[i];
		total += money[i];
		if (money[i] > maxmoney)
			maxmoney = money[i];
		i++;
	}

	parametric(maxmoney, total+1);
	cout << cur_k << '\n';
	return 0;
}