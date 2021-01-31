#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, k;
LL res = 1;
int main(void) {
	while(cin >> n >> k) {
		res = 1;
		for(LL i = 2; i * i <= k; i++) {
			LL kcnt = 0, mcnt = 0;
			while( k % i == 0) {
				kcnt++;
				k /= i;
			}
			if(kcnt) {
				for(LL j = i; j <= n; j *= i)
					mcnt += n / j;
				for(LL j = 0; j < min(kcnt, mcnt); j++)
					res *= i;
			}
			if(k < i)
				break;
		}
		if(k > 1 && k <= n)
			res *= k;
		cout << res << '\n';
	}
	return 0;
}


		
