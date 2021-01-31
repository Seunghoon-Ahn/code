#include <bits/stdc++.h>
using namespace std;
const int div_N = 1000000007;
int D;
vector <int> g[10];
long long dp[10][100003];
long long res;

long long make_dp(int n, int t) {
	if(t == D) {
		if(n == 7)
			return 1;
		else
			return 0;
	}
	long long tmp = dp[n][t];
	if(tmp != -1)
		return tmp;
	dp[n][t] = 0;
	for(int next : g[n]) {
		dp[n][t] += make_dp(next, t+1);
		dp[n][t] %= div_N;
	}
	return dp[n][t] % div_N;
}



int main(void) {
	memset(dp, -1, sizeof(dp));
	cin >> D;
	g[0].push_back(1);
	g[1].push_back(0);
	g[0].push_back(2);
	g[2].push_back(0);
	g[2].push_back(3);
	g[3].push_back(2); 
	g[1].push_back(3);
	g[3].push_back(1);
	g[1].push_back(4);
	g[4].push_back(1); 
	g[3].push_back(4);
	g[4].push_back(3); 
	g[3].push_back(5);
	g[5].push_back(3);
	g[4].push_back(5);
	g[5].push_back(4);
	g[4].push_back(6);
	g[6].push_back(4); 
	g[5].push_back(6);
	g[6].push_back(5); 
	g[5].push_back(7);
	g[7].push_back(5);
	g[6].push_back(7);
	g[7].push_back(6);
	
	res = make_dp(7, 0);
	cout << res << '\n';
	return 0;
}




