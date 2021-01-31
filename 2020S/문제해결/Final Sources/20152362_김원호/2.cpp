#include<iostream>
#include<string.h>

void make_prime(void);
int top_down(int a, int b);

bool is_prime[1130];
int prime[1130];
bool used[1130];
bool check;
int t, n, k, res, cnt;
long long int ans;

int knapsak(int a, int b)
{
	int res;

	if (prime[a] > n)
		return 0;

	if (b == 1)
	{
		res = prime[a] + knapsak(a + 1, 1) + knapsak(a + 1, 0);

		if (res == n)
			ans++;
	}
	else
		return knapsak(a + 1, 1) + knapsak(a + 1, 0);
}

int main(void)
{
	memset(used, false, sizeof(used));
	make_prime();

	/*scanf("%d", &t);

	for (int i = 0; i < t; i++)
	{
		scanf("%d %d", &n, &k);

	}*/
	n = 24;
	k = 2;
	res = 0;
	cnt = 0;
	//for (int i = 0; prime[i] <= n; i++)
	//{
	//	if (bottom_up(n, k, i) == n)
	//		ans++;
	//}
	ans = knapsak(0, 1) + knapsak(0, 0);
	printf("%d\n", ans);

	//for (int i = 0; i < 30; i++)
	//	printf("%d : %d\n", i, prime[i]);
}

//int sum_of_prime(int a, int b)
//{
//	if (b == 0)
//	{
//		if (a == 0)
//		{
//			ans++;
//			return 1;
//		}
//		else
//			return 0;
//	}
//
//	for (int i = 0; prime[i] <= a; i++)
//	{
//		if (used[i] == true)
//			continue;
//		
//		used[i] = true;
//
//		int remain = a - prime[i];
//		if (sum_of_prime(remain, b - 1) == 1)
//		{
//			used[i] = true;
//			check = true;
//		}
//		else
//			used[i] = false;		
//	}
//
//	if (check == true)
//		return 1;
//	else
//		return 0;
//}

int top_down(int a, int b)
{
	int res;

	if (b == 0)
	{
		if (a == 0)
		{
			ans++;
			return 1;
		}
		else
			return 0;
	}
	for (int i = 0; i < b; i++)
	{
		
	}
}


void make_prime(void)
{
	for (int i = 0; i < 1130; i++)
	{
		is_prime[i] = true;
	}

	is_prime[0] = is_prime[1] = false;

	for (int i = 2; i < 1130; i++)
	{
		if(is_prime[i] == true)
			for (int j = i * i; j < 1130; j += i)
			{
				is_prime[j] = false;
			}
	}
	int j = 0;
	for (int i = 0; i < 1130; i++)
	{
		if (is_prime[i] == true)
			prime[j++] = i;
	}
}
