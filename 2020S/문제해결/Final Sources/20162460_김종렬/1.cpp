#include<iostream>
long N = 0;
int** map;
int count[3] = { 0,0,0 };

void check(int size, int x, int y)
{
	if (size == 0) return;
	int num = map[x][y];
	bool filledSame = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (num != map[i + x][j + y])
			{
				filledSame = false;
				
				for(int k = 0; k < size; k+= size/3)
					for (int l = 0; l < size; l += size / 3)
					{
						check(size / 3, k + x, l + y);
					}
				return;
			}
		}
	}
	if (filledSame) count[num + 1]++;
}


int main()
{
	std::cin >> N;

	map = new int*[N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			std::cin >> map[i][j];
		}
	}
	check(N, 0,0);
	std::cout << count[0] << std::endl;
	std::cout << count[1] << std::endl;
	std::cout << count[2] << std::endl;
}