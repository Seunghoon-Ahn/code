#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
typedef pair<int, long long> p;
typedef long long ll;

int N, M; //도시수 버스수
int S, E; //출발, 도착
ll val = 1e9;
int check[1003];
vector <p> b[1003];
void going(int a, ll cur);

int main(void)
{
	int tmp1, tmp2, tmp3;

	cin >> N;
	cin >> M;

	for (int i = 0; i < M; i++) {
		cin >> tmp1 >> tmp2 >> tmp3;
		b[tmp1].push_back({ tmp2, tmp3 });
	}
	cin >> S >> E;

	going(S, 0);

	cout << val;
	return 0;
}

void going(int a, ll cur) {

	if (a == E) {
		if (val > cur)
			val = cur;
		return;
	}

	for (int i = 0; i < b[a].size(); i++) {
		if (!check[b[a][i].first]) {
			check[b[a][i].first] = 1;
			going(b[a][i].first, b[a][i].second + cur);
			check[b[a][i].first] = 0;
		}
	}
}