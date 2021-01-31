// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "vector"
#include "queue"
#include "stack"
#include "algorithm"

using namespace std;

vector <int> v;

int n, m;

bool D(int x) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x / v[i];
	}
	//cout<<x<<"  -  " << sum;
	if (sum < m)
	{
		//cout << "avil****\n";
		return true;
	}

	else
	{
		//cout << "dis****\n";
		return false;
	}

}

int main() {
	cin >> n >> m;
	int temp;

	if (n == 1) cout << m;

	else {
		for (int i = 0; i < n; i++) {
			cin >> temp;
			v.push_back(temp);
		}

		sort(v.begin(), v.end());


		int mid;
		int cnt = 1;
		bool check = false;
		while (1) {
			if (D(cnt*v[0]) && !D((cnt + 1)*v[0])) {
				check = true;
				//cout << "들어옴";
				int low = cnt* v[0];
				int high = (cnt + 1)*v[0];

				while (low <= high) {
					mid = (low + high) / 2;
					//cout<<"-------" << mid<<'\n';
					if (D(mid)) {
						low = mid + 1;
					}
					else {
						high = mid - 1;
					}
				}

			}
			if (check) break;
			cnt++;
		}
		cout << mid;
	}

	
	return 0;
}