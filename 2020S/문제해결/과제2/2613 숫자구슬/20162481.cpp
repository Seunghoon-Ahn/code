#include <iostream>
#include <algorithm>
using namespace std;

int N, M;  // N-구슬의 갯수  M-그룹의 수
int marble[310] = { 0 };
int maxmarble = 0;
int total = 0, groupmax = 0;
int m_sum[310];
int m_sum_index = 1;

void parametric(int x, int y) {
	int cnt = 1;
	int mid = (x + y) / 2;
	int tmpsum = 0;

	if (x == y) {
		groupmax = mid;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (tmpsum + marble[i] <= mid)
			tmpsum += marble[i];
		else if (tmpsum + marble[i] > mid) {
			tmpsum = 0;
			tmpsum += marble[i];
			cnt++;
		}
	}

	if (cnt <= M)
		parametric(x, mid);
	else
		parametric(mid + 1, y);
}

void find_group(void) {
	int tmpsum = 0;
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		
		if ((M - cnt) == (N - i)) {
			for (i; i < N; i++) {
				m_sum[m_sum_index] = i;
				m_sum_index++;
			}
			break;
		}
		
		if (tmpsum + marble[i] <= groupmax)
			tmpsum += marble[i];
		else if (tmpsum + marble[i] > groupmax) {
			tmpsum = 0;
			tmpsum += marble[i];
			m_sum[m_sum_index] = i;
			m_sum_index++;
			cnt++;
		}
	}
	m_sum[m_sum_index] = N;

	for (int i = M; i > 0; i--)
		m_sum[i] -= m_sum[i - 1];
}

int main(void) {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> marble[i];
		total += marble[i];
		if (maxmarble < marble[i]) maxmarble = marble[i];
	}

	parametric(maxmarble, total);
	find_group();

	cout << groupmax << '\n';

	if (M == 1) cout << m_sum[1];
	else if (M >= 2) {
		for (int i = 1; i <= M; i++) {
			cout << m_sum[i];
			if (i < M) cout << ' ';
		}
	}
	cout << '\n';

	return 0;
}