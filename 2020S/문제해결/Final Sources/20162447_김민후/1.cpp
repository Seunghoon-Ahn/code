#include <stdio.h>
#include <vector>
using namespace std;
char paper[20000][20000];
int n, cntz = 0, cntm = 0, cntp = 0;
void gogo(int a, int b, int aa, int bb)
{
	int one = paper[a][b], chk = true;
	int size = aa - a + 1;
	for (int i = a; i <= aa; i++)
	{
		for (int j = b; j <= bb; j++)
		{
			if (paper[i][j] != one)
			{
				chk = false;
				for (int ii = a; ii <= aa; ii += size / 3)
					for (int jj = b; jj <= bb; jj += size / 3)
						gogo(ii, jj, ii + size / 3 - 1, jj + size / 3 - 1);
				break;
			}
		}
		if (!chk) break;
	}
	if (chk)
	{
		//printf("%d %d %d %d : %d, %d\n", a, b, aa, bb,size,one);
		if (one == 1) cntp++;
		else if (one == -1) cntm++;
		else if (one == 0) cntz++;
		//else printf("?!");
	}
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) scanf("%d", &paper[i][j]);
	gogo(0, 0, n - 1, n - 1);
	printf("%d\n%d\n%d\n",cntm,cntz,cntp);
	return 0;
}

/*
9
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
0 0 0 1 1 1 -1 -1 -1
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 0 1
0 1 -1 0 1 -1 0 1 -1
0 -1 1 0 1 1 0 1 -1
0 1 -1 1 0 -1 0 1 -1

3
1 1 1
1 1 1
1 1 1
*/