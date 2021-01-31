#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#pragma warning(disable:4996)

using namespace std;


int dp[302][302];
bool graph[302][302];//edge��, graph[from][to] = true�� from->to �� ����
int cost[302][302];//������

int N, M, K;//�� ���ü�, ���� ���ù�ȣ, edge��
int pathCost;

int main() {
	memset(graph, false, sizeof(graph));
	memset(cost, 0, sizeof(cost));

	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (a >= b) continue;//�ǵ��ư��� ���� �ƿ��ȸ����
		graph[a][b] = true;
		if (cost[a][b] < b) cost[a][b] = c;//���� �����͸� ����
	}
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= M; j++) dp[i][j] = -10000;
	}

	for (int diagonal = 1; diagonal <= M; diagonal++) {
		for (int i = 1; i <= M; i++) {
			int j = i + diagonal;
			//printf("i=%d j=%d\n", i, j);
			int tmpCost = 0;
			for (int k = i; k <= j; k++) {
				if (graph[i][k] && graph[k][j]) {
					if (tmpCost < dp[i][k] + dp[k][j])
						tmpCost = dp[i][k] + dp[k][j];
					//printf("k=%d,tmpCost=%d\n",k,tmpCost);
				}
			}
			if (graph[i][j]) {
				if (cost[i][j] > tmpCost)
					dp[i][j] = cost[i][j];
				else dp[i][j] = tmpCost;
			}
			else dp[i][j] = tmpCost;
		}
	}
	/*for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%3d", dp[i][j]);
		}
		printf("\n");
	}*/


	printf("%d\n", dp[1][M]);

	return 0;
}
