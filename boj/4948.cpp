#include <bits/stdc++.h>

using namespace std;

int sieve[250001];
void func() {
	sieve[1] = true;

	for(int p = 2; p * p <= 250000; p++) {
		if(sieve[p])
			continue;
		for(int i = p * p; i <= 250000; i += p)
			sieve[i] = true;
	}
}

int main(void) {
	func();
	while(1) {
		int a;
		res = 0;
		cin >> a;
		if(a == 0)
			break;
		for(int i = a + 1; i <= a * 2; i++)
			if(sieve[i] == false)
				res++;

		cout << res << '\n';
	}
	return 0;
}

