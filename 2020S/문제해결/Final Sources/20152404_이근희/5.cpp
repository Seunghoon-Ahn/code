#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int total;
int arr[22][22];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d", &arr[i][j]);
			total+=arr[i][j];
		}
	}
	int minv=1e9;
	for(int i=1; i<n; i++){
		for(int j=i+1; j<=n; j++){
			int a=arr[i][j]+arr[j][i];
			int b=total-a;
			if(a>b)
				minv=min(minv, a-b);
			else
				minv=min(minv, b-a);	
		}
	}
	printf("%d\n", minv);
}
