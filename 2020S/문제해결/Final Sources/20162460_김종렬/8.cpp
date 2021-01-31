#include<iostream>
#include<queue>

typedef struct
{
	std::vector<int> pre;
}Student;

Student students[101];

int check[101];
int n, m;
int max = 0;

void get_max(int num, int saved)
{
	if (num > n)
	{
		if (max < saved)
		{
			max = saved;
		}
	}
	for (int i = num; i <= n; i++)
	{
		for (int j : students[i].pre)
		{
			if (check[j] == 0)
			{
				check[j] = 1;
				get_max(i + 1, saved + 1);
				check[j] = 0;
			}
		}
	}
}

int main()
{
	std::cin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		int a, b;
		std::cin >> a >> b;
		students[a].pre.push_back(b);
	}
	get_max(1, 0);
	std::cout << max <<std::endl;
}