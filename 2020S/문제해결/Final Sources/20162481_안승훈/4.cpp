#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
typedef pair<int, int> p;

int N, M, K; // N 도시 수 M 목적지 K 항로 수
vector <p> f[302]; //항로  시작점 , first 도착지 second 가중치
int curmax = 0;

void fly(int a, int val);

int main(void)
{
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);

	cin >> N >> M >> K;

	for (int i = 0; i < K; i++) {
		int tmp1, tmp2, tmp3;
		cin >> tmp1 >> tmp2 >> tmp3;
		if (tmp1 < tmp2) { //거꾸로가는 경로 제외
			f[tmp1].push_back({ tmp2, tmp3 });
		}
	}

	int food = 0;
	
	fly(1, 0);

	cout << curmax;
	return 0;
}

void fly(int a, int val) {
	if (a == M) {
		if (curmax < val)
			curmax = val;
		return;
	}

	for (int i = 0; i < f[a].size(); i++) {
		fly(f[a][i].first, val + f[a][i].second);
	}

	return;
}
