#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
int n;
bool isprime[8000000];

void prime(void) {
	memset(isprime, 1, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	int tmp = int(sqrt(8000000));
	for(int i = 2; i <= tmp; i++)
		if(isprime[i])
			for(int j = i * i; j <= 8000000; j += i)
				isprime[j] = false;
}

int main(void) {
	prime();
	cin >> n;
	vector <int> v;
	for(int i = 0; i < 8000000; i++)
		if(isprime[i])
			v.push_back(i);
	cout << v[n-1] << '\n';
	return 0;
}

