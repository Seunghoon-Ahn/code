#include <iostream>

using namespace std;

int main(void) {
	int f[101][101] = {0};
	int res[101][101] = {0};
	int flower = 0, vase = 0;
	int tmp = 0;

	cin>>flower>>vase;
	for( int i = 1; i <= flower; i++)
		for(int j = 1; j <= vase; j++)
			cin>>f[i][j];
//여기까지 입력

	for(int i = 1; i <= vase - flower + 1; i++)
		res[1][i] = f[1][i];

	for( int i = 2; i <= flower; i++) {
		tmp = res[i-1][i-1];
		for(int j = i; j <= vase - flower + i; j++) {
			for(int k = i - 1; k < j; k++)
				if(tmp < res[i-1][k])
					tmp = res[i-1][k];

			res[i][j] = tmp + f[i][j];
		}
	}
	
	tmp = res[flower][flower];
	for(int i = flower; i <= vase; i++)
		if(tmp < res[flower][i])
			tmp = res[flower][i];
	
	cout<<tmp;
	return 0;
}
