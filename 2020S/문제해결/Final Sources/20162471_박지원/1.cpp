#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int arr[2200][2200] = { 0 };
int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;

void dev(int s_r, int e_r, int s_c, int e_c)
{
	int plus = (e_r - s_r + 1) / 3;
	int value = (e_r - s_r + 1)*(e_c - s_c + 1);
	
	int sum = 0;
	bool same = true;
	int rule = arr[s_r][s_c];

	//ÃÖ¼Ò
	if (value == 9)
	{
		for (int i = s_r; i <= e_r; i++)
		{
			for (int j = s_c; j <= e_c; j++)
			{
				sum += arr[i][j];
				if (arr[i][j] != rule)
				{
					same = false;
					break;
				}
			}
			if (same == false)
			{
				break;
			}			
		}

		if (same == true)
		{
			if (sum == -9)
			{
				cnt1++;
				return;
			}
			else if (sum == 0)
			{
				cnt2++;
				return;
			}
			else if (sum == 9)
			{
				cnt3++;
				return;
			}
		}
		else
		{
			for (int i = s_r; i <= e_r; i++)
			{
				for (int j = s_c; j <= e_c; j++)
				{
					if (arr[i][j] == -1)
					{
						cnt1++;
					}
					else if (arr[i][j] == 0)
					{
						cnt2++;
					}
					else
					{
						cnt3++;
					}
				}
			}
		}
		return;
	}

	
	for (int i = s_r; i <= e_r; i++)
	{
		for (int j = s_c; j <= e_c; j++)
		{
			sum += arr[i][j];
			if (arr[i][j] != rule)
			{
				same = false;
				break;
			}
		}
		if (same == false)
		{
			break;
		}
	}
	if (same == true)
	{
		if (sum == -value)
		{
			cnt1++;
			return;
		}
		else if (sum == 0)
		{
			cnt2++;
			return;
		}
		else if (sum == value)
		{
			cnt3++;
			return;
		}
	}
	else
	{
		for (int a = 0; a < 3; a++)
		{
			for (int b = 0; b < 3; b++)
			{
				dev(s_r + a*plus, (s_r + (a + 1)*plus)-1, s_c + b*plus, (s_c + (b + 1)*plus)-1);
			}
		}
	}
}

int main()
{
	int n,num;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> num;
			arr[i][j] = num;
		}
	}
	dev(1, n, 1, n);
	cout << cnt1 << "\n";
	cout << cnt2 << "\n";
	cout << cnt3 << "\n";

	return 0;
}