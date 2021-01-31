#include <bits/stdc++.h>

using namespace std;

int divide(int a, int b) {
	int res = 0;
	while(1) {
		if(a % b)
			return res;
		else {
			a /= b;
			res++;
		}
	}
}

int main(void) {
	int num;
	cin >> num;
		
	int five = 0, two = 0;

	for(int i = 1; i <= num; i++) {
		five += divide(i, 5);
		two += divide(i, 2);
	}
	cout << min(five, two) << '\n';

	return 0;
}
