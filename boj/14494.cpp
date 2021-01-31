#include <iostream>
#include <algorithm>
using namespace std;
int map[1003][1003];

int main(void) {
	int x, y;
	cin >> x >> y;

	for(int i = 1; i <= 1002; i++)
		map[i][1] = map[1][i] = 1;
	
	for(int i = 2; i <= y; i++)
		for(int j = 2; j <= x; j++)
			map[i][j] = ((map[i-1][j] + map[i-1][j-1]) % 1000000007 + map[i][j-1]) % (1000000007);

	cout << map[y][x] << '\n';
	return 0;
}


			

