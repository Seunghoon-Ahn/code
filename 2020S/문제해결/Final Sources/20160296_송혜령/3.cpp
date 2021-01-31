#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdlib>
#include<vector>

#define NUM 1121

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int T;
int N, K;
bool bSieve[NUM];
int dp[NUM][15];
vector<int> prime;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	bSieve[0] = bSieve[1] = true;
	for (int i = 2; i*i < NUM; ++i)
	{
		if (!bSieve[i])
		{
			for (int j = i*i; j < NUM; j += i)
				bSieve[j] = true;
		}
	}

	for (int i = 2; i < NUM; ++i)
	{
		if (!bSieve[i]) //소수라면
		{
			dp[i][1] = 1;
			prime.push_back(i);
		}
	}

	/*
	int primeSize = prime.size();
	for (int i = 0; i < primeSize; ++i)
	{
		for (int j = NUM; j > 0; --j)
		{
			dp[j] += dp[j - prime[i]];
		}
	}
	*/

	for (int i = NUM; i > 2; --i)
	{
		for (int j = NUM - 1; j > 1; --j){}
	}

	for (int num = 3; num <= 14; ++num) //K
	{
		for (int i = NUM; i > 2; --i) //N
		{
			for (int j = NUM - 1; j >= 2; --j)
			{
				if (!bSieve[j])
				{
					dp[i][num] += dp[i - j][num-1];
				}
			}
		}
	}

	cin >> T;
	while (T--)
	{
		cin >> N >> K;

		cout << dp[N][K] << '\n';
	}



	return 0;
}

/*
12
24 3
24 2
2 1
1 1
4 2
18 3
17 1
17 3
17 4
100 5
1000 10
1120 14
*/