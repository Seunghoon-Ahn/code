#include <iostream>
#include <cstdio>
#define max(a,b) a > b ? a : b
using namespace std;

int main(void) {
	int stat[1001][2] = {0};
	int team[1001][16][16] = {0};
	int tmp = 1;

	while(scanf("%d %d", &stat[tmp][0], &stat[tmp][1]) > 0)
		tmp++;

	for( int man = 1; man <= tmp; man++) {
		for(int i = 0; i <= 15; i++) {
			for(int j = 0; j <= 15; j++) {
				team[man][i][j] = team[man-1][i][j];
				if(i != 0)
					team[man][i][j] = max(team[man][i][j], team[man-1][i-1][j] + stat[man][0]);
                if(j != 0)
                	team[man][i][j] = max(team[man][i][j], team[man-1][i][j-1] + stat[man][1]);
			}
		}
	}
	cout<<team[tmp-1][15][15];
	return 0;
}
