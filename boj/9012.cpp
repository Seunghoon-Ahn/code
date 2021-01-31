#include <iostream>
#include <algorithm>
#include <stack>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> v;
int tmp;
int main(void)
{
	int a;
	int check = 0;
	char arr[101];
	cin >> a;
	tmp = a;
	while(a--) {
		check = 0;
		memset(arr, 0, sizeof(arr));
		stack<int> s;
		
		scanf("%s", arr);
		for(int i = 0; i < strlen(arr); i++) {
			if(arr[i] == '(')
				s.push(1);
			else if (arr[i] == ')') {
				if(s.empty()) {
					check = 1;
					v.push_back(2);
					break;
				}
				else
					s.pop();
			}
		}
		if(check)
			continue;
		if(s.empty())
			v.push_back(1);
		else
			v.push_back(2);
	}

	for(int i = 0; i < tmp; i++) {
		if(v[i] == 1)
			cout << "YES\n";
		else if (v[i] == 2)
			cout << "NO\n";
	}

	return 0;
}


		
