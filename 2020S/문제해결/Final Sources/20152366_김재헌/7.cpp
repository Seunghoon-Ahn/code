#include <iostream>
#include <vector>
using namespace std;

int N, M;
int A, B;

int Line[1001][1001];
int Adj[1001];
int Dis[1001];

int main(void)
{

	int a, b, c;
	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			Line[i][j] = 100000;

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (Line[a][b] > c)
			Line[a][b] = c;
	}
	scanf("%d %d", &A, &B);

	for (int i = 2; i <= N; i++) {
		Adj[i] = 0;
		Dis[i] = 100000;
	}

	for (int i = 1; i <= N; i++) {
		 if (Line[A][i] != 0)
			Adj[i] = A;
			Dis[i] = Line[A][i];
	}
	
	for (int i = 1; i <= N; i++) {
		if (i == A)
			continue;

		for (int j = 1; j <= N; j++) {
			if (Dis[i] + Line[i][j] < Dis[j]) {
				Dis[j] = Dis[i] + Line[i][j];
				Adj[j] = i;
			}
		}
	}

	printf("%d", Dis[B]);
	
}