#include <bits/stdc++.h>
using namespace std;
int N, M;
vector <int> m;

int calcul(int money) {
	int cnt = 1;
	int curmoney = money;

	for(int i = 0; i < N; i++) {
		if(curmoney >= m[i])
			curmoney -= m[i];
		else {
			curmoney = money;
			cnt++;
			curmoney -= m[i];
		}
	}
	return cnt;
}

int main(void) {
	int max = 1, tmp, min = 0;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 0; i < N; i++) {
		cin >> tmp;
		m.push_back(tmp);
		if(i == 0)
			min = tmp;
		if(min < tmp)
			min = tmp;
		max += tmp;
	}
	int mid;
	while(1) {
		mid = (min + max) / 2;
		if(min == mid || min == max) break;
		int res = calcul(mid);
		if(res <= M)
			max = mid;
		else
			min = mid + 1;
	}
	cout << min << '\n';
	return 0;
}


