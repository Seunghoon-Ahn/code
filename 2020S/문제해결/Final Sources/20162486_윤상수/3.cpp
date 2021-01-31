#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 1120
#define HALF_MAX 560
bool data[1150];
bool rest[1000];

int TC,max_r;
int answer;
void Func(int n, int k,int chk);
int main()
{
	max_r = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		data[i] = false;
	for (int i = 2; i < MAX_SIZE; i++)
	{
		if (!data[i])
		{
			rest[max_r] = i;
			max_r++;
			for (int j = 2; j < HALF_MAX; j++)
			{
				if(i*j<=MAX_SIZE)
				data[i*j] = true;
			}
		}
	}
	scanf("%d", &TC);

	int n, k;
	for (int i = 0; i < TC; i++)
	{
		scanf("%d %d", &n, &k);
		answer = 0;
		Func(n, k,0);
		printf("%d\n", answer);
	}
	return 0;
}
void Func(int n, int k,int chk)
{
	printf("%d\n", n);
	int tmp;
	for (int i = chk; i < max_r; i++)
	{
		if (data[i] > n)
			return;
		tmp = 0;
		for (int j = 0; j < k; j++)
			tmp += data[chk + j];
		if ((n - data[i]) == 0 && k == 1)
			answer++;
		if (tmp<=n&&k>1)
			Func(n - data[i], k - 1, chk+1);
	}
}