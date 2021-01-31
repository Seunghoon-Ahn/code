#include <iostream>

using namespace std;

int arr[100001] = { 0 };
long long check, person, time;
long long result = 0;


void search(int s, int e)
{
	int mid;
	long long check_person;
	while(s <= e)
	{		
		mid = (s + e) / 2;
		check_person = 0;
		for (int i = 1; i <= check; i++)
		{
			//시간동안 검사		
			check_person += mid / arr[i];
			//cout << check_person;
		}
		if (check_person < person)
		{
			s = mid + 1;			
		}
		else if (check_person >= person)
		{
			e = mid - 1;
		}		
	}	
	result = s;
}

int main()
{
	
	cin >> check >> person;
	for (int i = 1; i <= check; i++)
	{
		cin >> time;
		arr[i] = time;
	}

	search(0, 2100000000);
	//search(0, 20);

	cout << result;
}