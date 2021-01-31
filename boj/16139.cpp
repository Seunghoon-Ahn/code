#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
string s;
int arr[202020][26];
int q;
int main(void) {
	char c;
	int tmp1, tmp2;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> s;
	s = ' ' + s;
	cin >> q;
	for(int i = 1; i <= s.length(); i++) {
		for(int j = 0; j < 26; j++) {
			if(j == (s[i] - 'a'))
				arr[i][j] = arr[i-1][j] + 1;
			else
				arr[i][j] = arr[i-1][j];
		}
	}
	for(int i = 0; i < q; i++) {
		cin >> c >> tmp1 >> tmp2;
		cout << arr[tmp2+1][c-'a'] - arr[tmp1][c-'a'] << '\n';
	}
	return 0;
}

