#include <iostream>
#define max(a, b) a > b ? a : b
using namespace std;
int main(void) {
	int num = 0, i = 0;
	int rank[301] = {0};
	int res[301] = {0};
	cin>>num;
	for(i = 1; i <= num; i++)
		cin>>rank[i];
	
	res[1] = rank[1];
	res[2] = rank[1] + rank[2];
	res[3] = max(rank[3] + res[1], rank[3] + rank[2]);
	
	for( i = 4; i <= num; i++)
		res[i] = max( rank[i] + res[i-2], rank[i] + rank[i-1] + res[i-3]);
	cout<<res[num];
	return 0;
}
