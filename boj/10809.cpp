#include <iostream>
#include <string>
using namespace std;
int arr[26];
int main(void) {
	string s;
	cin >> s;
	for(char i = 'a'; i <= 'z'; i++) {
		int check = 0;
		for(int j = 0; j < s.length(); j++) {
			if(s[j] == i) {
				arr[i - 'a'] = j;
				check = 1;
				break;
			}
		}
		if(!check)
			arr[i - 'a'] = -1;
	}

	for(int i = 0; i < 26; i++)
		cout << arr[i] << ' ';
	return 0;
}

