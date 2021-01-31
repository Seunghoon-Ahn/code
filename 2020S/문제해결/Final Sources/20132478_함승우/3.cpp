#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>

const int MAX_N = 1121;

using namespace std;

int T;
int board[MAX_N] = { 0 };
vector <int> prime;

int n, k;
int result = 0;

void eratose(int n);
void dfs(int now, int cnt, int rest);
int vis[MAX_N];
int p_size;

int main()
{
	eratose(MAX_N);

	int rest;
	int size = prime.size();
	//for (int i = 0; i < size; i++)
	//	printf("%d ", prime[i]);

	p_size = prime.size();

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> n >> k;

		result = 0;
		rest = n;
		memset(vis, 0, sizeof(vis)); 

		for (int j = 0; j < p_size; j++) {
			memset(vis, 0, sizeof(vis));
			dfs(j, 0, rest);
		}
		printf("%d\n", result);
		cin >> n;
	}
}

void dfs(int now, int cnt, int rest)
{
	if (vis[now] == true)
		return;

	vis[now] = true;	//µé·¶À½

	rest -= prime[now];
	cnt++;

	if (cnt > k || rest < 0)	//È½¼ö ÃÊ°úÇÏ°Å³ª ³²Àº°Ô ºÎÁ·ÇÏ¸é
		return;

	//printf("now : %d , rest : %d , cnt : %d\n", now, rest, cnt);

	if (cnt == k && rest == 0) { //µü ¶³¾îÁü
		result++;
		return;
	}
	else {
		for (int i = now; i < p_size; i++) {
			dfs(i, cnt, rest);
			vis[i] = false;
		}
	}
}

void eratose(int n)
{
	for (int i = 2; i*i < n; i++) {
		if (board[i] == 1)
			continue;
		for (int j = i*i; j < n; j += i) {
			board[j] = 1;
		}
	}

	for (int i = 2; i < n; i++) {
		if (board[i] == 0)
			prime.push_back(i);
	}
}