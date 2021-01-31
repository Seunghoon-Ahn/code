#include<cstdio>
#include<vector>
#include <iostream>
using namespace std;
int N;
int arr[1000][1000];
int visit[1000][1000];
int dx[4]= {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int ret[3];
void cal(int x, int y,int len) {
	int cur = arr[x][y];
	int clear = 1;
	for (int i = x; i < x + len; i++) {
		for (int j = y; j < y + len; j++) {
			if (arr[i][j] != cur) {
				cal(x,y,len/3);
				cal(x+(len/3), y, len / 3);
				cal(x+(len/3)*2, y, len / 3);
				cal(x, y+(len / 3), len / 3);
				cal(x, y+ (len / 3) * 2, len / 3);
				cal(x+ (len / 3), y+ (len / 3), len / 3);
				cal(x+ (len / 3) * 2, y+ (len / 3), len / 3);
				cal(x+ (len / 3), y+ (len / 3) * 2, len / 3);
				cal(x+ (len / 3) * 2, y+ (len / 3) * 2, len / 3);
				return;
			}
		}
	}
	if(clear==1)
		ret[cur + 1]++;
}

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &arr[i][j]);
	cal(0, 0, N);
	for (int i = 0; i < 3; i++)
		printf("%d\n", ret[i]);
}