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

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll N, M;
vector<ll> arr;

bool decision(ll time)
{
	ll sum = 0;
	for (int i = 0; i < N; ++i)
	{
		sum += (time / arr[i]);
	}

	if (sum >= M)
		return true;
	else
		return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	arr.resize(N);

	ll s = (ll)1e10, e = 0;
	cout << s << ' ' << e << '\n';
	for (int i = 0; i < N; ++i)
	{
		cin >> arr[i];
		s = min(s, arr[i]);
	}

	e = s * M;

	if (decision(s))
		cout << s << '\n';
	else {
		while (s + 1 < e)
		{
			ll mid = (s + e) / 2;
			if (decision(mid))
				e = mid;
			else
				s = mid;
		}
	}

	cout << e << '\n';

	return 0;
}

/*
2 6
7
10

7 10
3
8
3
6
9
2
4

1 1000000000
1

8 1000000000
1
1
1
1
1
1
1
1
*/