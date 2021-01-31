#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct edg{
	int idx;
	int dst;
	int count;
};

vector<edg> gph[302];
int dp[302][302];

int dfs(int x, int k){
	if(dp[x][k]!=-1) return dp[x][k];
	dp[x][k]=0;
	for(int i=0; i<gph[x].size(); i++){
		edg nxt=gph[x][i];
		if(x>nxt.idx&&k>=1){
			dp[x][k]=max(dp[x][k], dfs(nxt.idx, k-1)+nxt.dst);
		}	
	}
	return dp[x][k];
}


int main()
{
	int n,m,k;
	scanf("%d %d %d", &n, &m,&k);
	for(int i=1; i<=k; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		gph[b].push_back({a,c, 0});
	}
	memset(dp, -1, sizeof(dp));	
	for(int i=1; i<=k; i++)
		dp[1][i]=0;

	printf("%d", dfs(n, k));
}
