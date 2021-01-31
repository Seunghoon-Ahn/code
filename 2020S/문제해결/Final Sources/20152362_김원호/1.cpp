//#include<iostream>
//
//using namespace std;
//
//
//void divide(int x, int y, int n);
//
//int arr[5005][5005];
//int n, res, a, b, c;
//
//int main(void)
//{
//	scanf("%d", &n);
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			scanf("%d", &arr[i][j]);
//		}
//	}
//
//	divide(0, 0, n);
//	printf("%d\n%d\n%d\n", a, b, c);
//}
//
//void divide(int x, int y, int n)
//{
//	int check = arr[x][y];
//
//	for (int i = x; i < x + n; i++)
//	{
//		for (int j = y; j < y + n; j++)
//		{
//			if (arr[i][j] != check)
//			{
//				check = -2;
//				break;
//			}
//		}
//		if (check == -2)
//			break;
//	}
//
//	if (check == -1)
//	{
//		a++;
//		return;
//	}
//	else if (check == 0)
//	{	
//		b++;
//		return;
//	}
//	else if (check == 1)
//	{
//		c++;
//		return;
//	}
//
//	int p = n / 3;
//	divide(x, y, p);
//	divide(x, y + p, p);
//	divide(x, y + (2 * p), p);
//	divide(x + p, y, p);
//	divide(x + (2 * p), y, p);
//	divide(x + p, y + p, p);
//	divide(x + (2 * p), y + (2 * p), p);
//	divide(x + (2 * p), y + p, p);
//	divide(x + p, y + (2 * p), p);
//
//}