#include <iostream>
#include <algorithm>

using namespace std;

bool prime[10000001];

int main(void) {
	prime[1] = true;
	for (int i = 2; i * i <= 10000000; i++) {
		if (prime[i])
			continue;
		for (int j = i * i; j <= 10000000; j += i)
			prime[j] = true;
	}

	long long a, b;
	cin >> a >> b;

	int res = 0;
	for (long long i = 2; i <= 10000000; i++) {
		if (prime[i])
			continue;
		long long cur = i * i;
		long long next;
		while (1) {
			if (cur < a) {
				next = cur * i;
				if (next % cur != 0)
					break;
				cur = next;
			}
			else if (a <= cur && cur <= b) {
				res++;
				next = cur * i;
				if (next % cur != 0)
					break;
				cur = next;
			}

			else if (cur > b)
				break;
		}
	}
	cout << res << '\n';

	return 0;
}
