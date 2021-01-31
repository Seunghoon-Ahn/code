#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool prime[1120];
vector<int> v;
int dp[1124][15];

int main(){
	for(int i=2; i<=1120; i++){
		prime[i]=true;
	}
	for(int i=2; i*i<=1120; i++){
		if(!prime[i]) continue;
		for(int j=i*i; j<=1120; j+=i){
			prime[j]=false;
		}
	}
	for(int i=2; i<=1120; i++){
		if(prime[i]) v.push_back(i);
	}
	
	
	int t;
	scanf("%d", &t);
	while(t--){
		int n, k;
		scanf("%d %d", &n, &k);
		memset(dp,0, sizeof(dp));
		dp[0][0]=1;
		for(int i=0; i<v.size(); i++){
			for(int j=1120; j>0; j--){
				for(int x=1; x<=k; x++){
					if(j-v[i]>=0){
						dp[j][x]+=dp[j-v[i]][x-1];
				}
			}
		}
	}
	printf("%d\n", dp[n][k]);
	}
}
