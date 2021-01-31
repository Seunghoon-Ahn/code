#include <iostream>
#include <cmath>
using namespace std;

int N; //총 사탕 갯수
int candy_total = 0; //사탕값 합
int candy_var = 0;   //사탕 종류
int candy_zero = 1;  //0원 갯수
long long num_case[500002];
int candy[51][2]; //[0]사탕값 [1]사탕 갯수

bool is_prime(int n) {
	if (n == 1)
		return false;
	for (int i = 2; i <= sqrt(n); i++)
		if (n%i == 0)
			return false;
	return true;
}

int is_exist(int n, int max) {
	for (int i = 1; i <= max; i++)
		if (n == candy[i][0])
			return i;
	return 0;
}

int main(void) {
	
	int ncandy, loc;

	cin >> N;
	
	for (int i = 1; i <= N; i++) {
		cin >> ncandy;
		
		if (ncandy == 0) candy_zero++;
		else {
			candy_total += ncandy;
			if (loc = is_exist(ncandy, candy_var))
				candy[loc][1]++;
			else {
				candy_var++;
				candy[candy_var][0] = ncandy;
				candy[candy_var][1] = 1;
			}
		}
	}
	num_case[0] = 1;
	int sub;
	for (int i = 1; i <= candy_var; i++) {
		for (int cur_total = candy_total; cur_total >= 0; cur_total--) {
			for (int cnt = 1; cnt <= candy[i][1]; cnt++) {
				if ((sub = cur_total - candy[i][0] * cnt) < 0)
					break;
				num_case[cur_total] += num_case[sub];
			}
		}
	}

	long long res = 0;

	for (int i = 1; i <= candy_total; i++)
		if (is_prime(i))
			res += num_case[i];

	res = res * (long long)candy_zero;
	//0인 사탕 갯수 +1 곱해줌
	//0인 사탕이 2개면 (0, 1, 2) 3가지 포함 가능
	cout << res;

	return 0;
}
