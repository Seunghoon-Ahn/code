#include <iostream>
#include <algorithm>
using namespace std;
int N, M;
int x1, x2, y1, y2;
int in[1026][1026];
long long sum[1026][1026];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			cin >> in[i][j];
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + in[i][j];
		}
	}
	for(int i = 0; i < M; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		cout << sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1] << '\n';
	}
	return 0;
}
