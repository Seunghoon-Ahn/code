#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
#define MAX 2190

using namespace std;

vector<unsigned int> time;//각 심사대 걸리는 시간
int N;//심사대 수
unsigned int M;//심사받을 사람 수
long long totalTime;//총 걸린시간

int main() {
	totalTime = 0;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		unsigned int t;
		scanf("%d", &t);
		time.push_back(t);
	}
	sort(time.begin(), time.end());
	for (int i = 0; i < time.size(); i++) {
		printf("%d\n", time[i]);
	}



	return 0;
}