#include <iostream>
#include <algorithm>

using namespace std;

typedef long long intt;

intt N, M, min_t, from, to, mid;
intt time[100000];

bool possible(intt limit) {
	intt sum = 0;
	for (int i = 0; i < N; i++) {
		sum += limit / time[i];
		if (sum >= M) return true;
	}
	return false;
}

int main() {
	cin >> N >> M;
	min_t = 1000000000;
	for (int i = 0; i < N; i++) {
		cin >> time[i];
		min_t = min(min_t, time[i]);
	}

	from = 1;
	to = min_t * M;
	while (from < to) {
		mid = (from + to) / 2;
		if (possible(mid)) {
			to = mid;
		}
		else {
			from = mid + 1;
		}
	}
	cout << from;
}