#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int arr[2190][2190];
int con[3];
void divide(int x, int y, int num){
	int chk=0;
	for(int i=x; i<x+num; i++){
		for(int j=y; j<y+num; j++){
			if(arr[x][y]!=arr[i][j]){
				chk=1;
				break;
			}
		}
	}
	if(chk==0){
		if(arr[x][y]==-1)
			con[0]+=1;
		if(arr[x][y]==0)
			con[1]+=1;
		else{
			con[2]+=1;
		}
		return;		
	}
	divide(x,y,num/3);
	divide(x+num/3,y,num/3);
	divide(x+num/3*2,y,num/3);
	divide(x,y+num/3,num/3);
	divide(x+num/3,y+num/3,num/3);
	divide(x+num/3*2,y+num/3,num/3);
	divide(x,y+num/3*2,num/3);
	divide(x+num/3,y+num/3*2,num/3);
	divide(x+num/3*2,y+num/3*2,num/3);
	return;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d", &arr[i][j]);
		}
	}
	divide(1,1,n);
	for(int i=0; i<=2; i++){
		printf("%d\n", con[i]);
	}
}
