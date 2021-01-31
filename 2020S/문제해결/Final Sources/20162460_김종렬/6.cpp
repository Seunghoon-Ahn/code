#include<iostream>
#include<queue>

typedef struct
{
	int x, y;
} Cheese;

std::vector<Cheese> cList;

int n, m;
int map[101][101];
int cNum = 0;

bool check_closed(int x, int y)
{
	if (map[x][y] != 0) return true;
	if (x == 0 || y == 0 || x == m || y == n) return false;

	//std::cout << x << " " << y << std::endl;
	bool result = true;
	map[x][y] = 2;
	//map[x - 1][y] = 2;
	result &= check_closed(x - 1, y);

	if(result)
	result &= check_closed(x + 1, y);
	
	if(result)
	result &= check_closed(x, y - 1);
	
	if(result)
	result &= check_closed(x, y + 1);
	//map[x + 1][y] = 0;
	map[x][y] = 0;
		
	return result;
}

int main()
{
	std::cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cin >> map[j][i];
			if (map[j][i] == 1)
			{
				Cheese newC;
				cNum++;
				newC.x = j;
				newC.y = i;
				cList.push_back(newC);
			}
		}
	}
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << map[j][i];
		}
		std::cout << std::endl;

	}*/
	int time = 0;
	while (cNum != 0)
	{
		time++;
		std::vector<Cheese> newList;
		std::vector<Cheese> removeList;
		for (Cheese c: cList)
		{
			int edgeCount = 0;
			//std::cout << c.x << " " << c.y << std::endl;
			//std::cout << c.x << " " << c.y<<std::endl;
			if (!check_closed(c.x - 1, c.y)) edgeCount++;
			if (!check_closed(c.x + 1, c.y)) edgeCount++;
			if (!check_closed(c.x, c.y - 1)) edgeCount++;
			if (!check_closed(c.x, c.y + 1)) edgeCount++;

			
			//std::cout << "adsf";
			if (edgeCount < 2)
			{
				newList.push_back(c);

			}
			else
			{
				removeList.push_back(c);
				cNum--;
			}
		}
		cList = newList;
		for (Cheese c : removeList)
		{
			map[c.x][c.y] = 0;
		}
	}
	std::cout << time << std::endl;
}