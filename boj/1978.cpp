#include <bits/stdc++.h>

using namespace std;

int cnt = 0;
void func(int a) {
	for(int i = 2; i * i <= a; i++) {
		if(a % i == 0)
			return;
	}
	if(a != 1)
		cnt++;
	return;
}

int main(void) {
	int num;
	int tmp;

	cin >> num;
	for(int i = 0; i < num; i++) {
		cin >> tmp;
		func(tmp);
	}

	cout << cnt;
	return 0;
}
