#include <iostream>

#define MAX_N 100001

int N, M;
int T[MAX_N];

bool check_poss_time(int min);
int param_search(int start_t, int end_t);

int main(void)
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &T[i]);
	int start_t = 1;
	int end_t = 1000000000;
	int res = param_search(start_t, end_t);

	printf("%d", res);
}

int param_search(int start_t, int end_t) {
	int mid = (start_t + end_t) / 2;
	if (end_t - start_t == 1) {
		if (check_poss_time(start_t))
			return start_t;
		else
			return end_t;
	}
	else if (start_t == end_t)
		return start_t;


	if (check_poss_time(mid))
		return param_search(start_t, mid);
	else
		return param_search(mid + 1, end_t);
}

bool check_poss_time(int min) {
	int left = M;
	for (int i = 0; i < N; i++) {
		left -= min / T[i];
		if (left <= 0)
			return true;
	}

	return false;
		
}