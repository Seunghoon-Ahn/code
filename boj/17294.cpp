#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
string num;

int main(void) {
	cin >> num;
	int gap = num[0] - num[1];
	for(int i = 1; i < num.length(); i++) {
		if(num[i-1] - num[i] != gap) {
			cout << "흥칫뿡!! <(￣ ﹌ ￣)>\n";
			return 0;
		}
	}
	cout << "◝(⑅•ᴗ•⑅)◜..°♡ 뀌요미!!\n";
	return 0;
}


