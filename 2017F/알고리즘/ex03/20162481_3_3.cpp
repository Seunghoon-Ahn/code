//18계단 여러가지 종교
#include <iostream>
#include <cstdio>

using namespace std;

int matrix[50001] = {0};
int rank[50001] = {1};

int find(int a) {
	if(a == matrix[a]) 
		return a;
	else 
		return (matrix[a] = find(matrix[a]));
}

void union_node(int a, int b) {
	int tmp;
	a = find(a);
	b = find(b);

	if(a == b) 
		return;
	if(rank[a] > rank[b]) {
		tmp = a;
		a = b;
		b = tmp;
	}

	matrix[a] = b;
	if(rank[a] == rank[b]) 
		rank[b]++;
}

int main(void) {
	int N, M;
	int a, b, tmp;
	int res = 0;

	scanf("%d %d", &N, &M);

	for(int i = 1; i <= N; i++)
		matrix[i] = i;

	for(int i = 1; i <= M; i++) {
		scanf("%d %d", &a, &b);
		union_node(a, b);
	}

	for(int i = 1; i <= N; i++)
		if(matrix[i] == i)
			res++;

	cout<<res;
	return 0;
}
