#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
#define MAX 2190

using namespace std;

vector<unsigned int> time;//�� �ɻ�� �ɸ��� �ð�
int N;//�ɻ�� ��
unsigned int M;//�ɻ���� ��� ��
long long totalTime;//�� �ɸ��ð�

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