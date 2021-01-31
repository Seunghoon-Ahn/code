#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
long long ans = 0, minn = 1, maxx, lans;
int t[1000001] = { 0 };
int min(int a, int b)
{
	return a > b ? b : a;
}
int calc(int time)
{
	int people = 0, i = 0;
	while (people < m && i<n)
	{
		people += time / t[i++];
	}
	if (people >= m) { lans = time;  return true; }
	else return false;

}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &t[i]);
	}
	sort(t, t + n);
	maxx = t[0] * m;
	maxx *= 2;
	while (minn <= maxx)
	{
		ans = (minn + maxx) / 2;
		//printf("%lld %lld %lld\n", minn, ans, maxx);
		if (calc(ans))
		{
			maxx=ans-1;
		}
		else
		{
			minn=ans+1;
		}
	}
	printf("%lld\n", lans);

}

/*
2 6 7 10

1 1000000000

7 10
3
8
3
6
9
2
4
*/