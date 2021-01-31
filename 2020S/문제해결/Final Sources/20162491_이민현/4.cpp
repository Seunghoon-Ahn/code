#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

int n, m, k;

int length[301]; // 출발지로부터 n번 도시까지으 ㅣ거리



vector <pair<int, int>> vt[301];

typedef struct edge {
	int s, e;
	int value;
	int level;
};

queue<edge> q;

int main(void) {
	memset(length, 0, sizeof(length));
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int s, e, v;
		cin >> s >> e >> v;
		if (s < e) {
			vt[s].push_back({ e, v });
		}
	}

	for (pair<int, int> p : vt[1]) {
		edge temp;
		temp.s = 1;
		temp.e = p.first;
		temp.value = p.second;
		temp.level = 1;
		q.push(temp);
	}

	while (!q.empty()) {
		edge tp = q.front();
		q.pop();
		
		if (length[tp.e] < length[tp.s] + tp.value && tp.level <= m - 1) {
			length[tp.e] = length[tp.s] + tp.value;
		}

		for (pair<int, int>p : vt[tp.e]) {
			edge temp;
			temp.s = tp.e;
			temp.e = p.first;
			temp.value = p.second;
			temp.level = tp.level + 1;
			q.push(temp);
		}

	}

	cout << length[n];
}