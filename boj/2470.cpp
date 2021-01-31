#include <bits/stdc++.h>
#define MAX 2100000000
using namespace std;
vector <int> liq;

int N;
int sav1, sav2, sum = MAX;

int main(void) {
	int tmp;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> tmp;
		liq.push_back(tmp);
	}
	sort(liq.begin(), liq.end());

	for(int i = 0; i < N; i++) {
		int index = upper_bound(liq.begin(), liq.end(), 0 - liq[i]) - liq.begin();
		if(index == N) {
			if(i == index - 1) 
				continue;
			int checksum = liq[i] + liq[index - 1];
			if(abs(checksum) < abs(sum)) {
				sav1 = liq[i];
				sav2 = liq[index - 1];
				sum = checksum;
			}
		}
		else if(index == 0) {
			if(i == index)
				continue;
			int checksum = liq[i] + liq[index];
			if(abs(checksum) < abs(sum)) {
				sav1 = liq[i];
				sav2 = liq[index];
				sum = checksum;
			}
		}
		else {
			int checksum1 = liq[i] + liq[index];
			int checksum2 = liq[i] + liq[index - 1];
			if(i == index - 1)
				checksum2 = MAX;
			if(i == index)
				checksum1 = MAX;

			if(abs(checksum1) < abs(checksum2)) {
				if(abs(checksum1) < abs(sum)) {
					sav1 = liq[i];
					sav2 = liq[index];
					sum = checksum1;
				}
			}
			else {
				if(abs(checksum2) < abs(sum)) {
					sav1 = liq[i];
					sav2 = liq[index - 1];
					sum = checksum2;
				}
			}
		}
	}
	cout << min(sav1, sav2) << ' ' << max(sav1, sav2) << '\n';
	return 0;
}
