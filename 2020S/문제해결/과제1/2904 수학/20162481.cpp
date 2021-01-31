#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_NUM 1000000 
using namespace std;

int arr[101][80000] = {0};
int primenum[MAX_NUM] = {0};
int tmp = 0;

void make_prime(void) {
	int ftmp = 1;
	for (int i = 2; i < MAX_NUM; i++)
		primenum[i] = i;
	
	for (int i = 2; i < MAX_NUM; i++) {
		if (primenum[i] == 0) 
			continue;
		for (int j = i + i; j <= MAX_NUM; j += i) 
			primenum[j] = 0;
	}

	for(int i = 2; i < MAX_NUM; i++)
		if (primenum[i] != 0) {
			arr[0][ftmp] = primenum[i];
			ftmp++;
		}
}

int main(void) {
	int N, i = 1;
	int num;
	int p = 2;
	int gcd = 1, gcdtry = 0;

	cin >> N;

	make_prime();

	while (i <= N) {
		int x = 1;

		cin >> num;
		arr[i][0] = num;

		while (num != 1) {
			p = arr[0][x];
			if (num % p == 0) {
				(arr[i][x])++;
				num /= p;
			}
			else 
				x++;
		}
		i++;
	}

	for (int x = 1; x < 80000; x++) {
		int tmpsum = 0;

		for (int y = 1; y <= N; y++)
			tmpsum += arr[y][x];
		gcd *= pow(arr[0][x], (tmpsum / N));

		for (int y = 1; y <= N; y++) {
			if (arr[y][x] < (tmpsum / N)) {
				gcdtry += (tmpsum / N) - arr[y][x];
			}
		}
	}

	cout << gcd << ' '<< gcdtry << '\n';
	
	return 0;
}