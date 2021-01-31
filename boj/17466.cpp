#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
	long long a, b, c = 1;
	cin >> a >> b;
	for(long long i = 1; i <= a; i++) {
		c = c * (i % b);
		if(c >= b)
			c = c % b;
	}
	cout << c;

	return 0;
}

