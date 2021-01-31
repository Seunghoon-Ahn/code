#include <bits/stdc++.h>

using namespace std;
int tc;
vector <long long> v;
vector <long long> res;

long long gcd(long long a, long long b) {
	    return b ? gcd(b, a % b) : a;
}

int main(void) {
	cin >> tc;
	for(int a = 0; a < tc; a++) {
		int cnt, tmp;
		long long sum = 0;
		cin >> cnt;
		v.clear();
		for(int i = 0; i < cnt; i++) {
			cin >> tmp;
			v.push_back(tmp);
		}

		for(int i = 0; i < cnt; i++) {
			for(int j = i; j < cnt; j++) {
				if(j == i)
					continue;
				else
					sum += gcd(v[i], v[j]);
			}
		}
		res.push_back(sum);
	}
	
	for(int i = 0; i < tc; i++)
		cout << res[i] << '\n';

	return 0;
}
