#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 65
using namespace std;
int map[MAX][MAX] = { 0 };
int N;
vector<char> res;

void DC(int x, int y, int num) {
	int tmp = 0;

	for (int i = x; i <= x + num - 1; i++) 
		for (int j = y; j <= y + num - 1; j++) 
			tmp += map[i][j];

	if (tmp == 0) res.push_back('0');
	else if (tmp == num*num) res.push_back('1');
	else {
		res.push_back('(');
		DC(x, y, num / 2);
		DC(x, y + num / 2, num / 2);
		DC(x + num / 2, y, num / 2);
		DC(x + num / 2, y + num / 2, num / 2);
		res.push_back(')');
	}
}

int main(void) {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			scanf("%1d", &map[i][j]);
	}

	DC(1, 1, N);

	for (int i = 0; i < res.size(); i++)
		cout << res[i];
	cout << '\n';

	return 0;
}