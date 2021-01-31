#include <bits/stdc++.h>

using namespace std;

void func(long long a) {
	for(long long i = 2; i*i <= a; i++) {
		if(a % i == 0)
			return;
	}
	if(a != 1)
		cout << a << '\n';
	return;
}

int main(void) {
	int a, b;
	cin >> a >> b;

	for(int i = a; i <= b; i++)
		func(i);
	return 0;
}
