#include<iostream>
#include<queue>

typedef struct
{
	int dest = 0;
	int point = 0;
} Load;

typedef struct
{
	std::vector<Load> loads;
} City;


City city[301];
int N, M, K;

int max = 0;
void find_yummyPath(int thisCity, int count, int yumPoint)
{
	if (count > M) return;
	if (thisCity == N && max < yumPoint)
	{
		max = yumPoint; return;
	}
	for(Load l : city[thisCity].loads)
	{
		if (l.dest > thisCity)
		{
			find_yummyPath(l.dest, count + 1, yumPoint + l.point);
		}
	}
}
int main()
{
	std::cin >> N >> M >> K;
	
	for (int i = 0; i < K; i++)
	{
		Load l;
		int c; 
		std::cin >> c;
		 std::cin >> l.dest;
		std::cin >> l.point;
		
		city[c].loads.push_back(l);
	}
	find_yummyPath(1, 1, 0);
	std::cout << max <<std::endl;
}