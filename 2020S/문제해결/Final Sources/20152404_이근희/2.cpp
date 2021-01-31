#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct edg {
	long long a;
	int time;
};

bool comp(const edg &a, const edg &b){
	if(a.a<b.a)
		return true;
	if(a.a==b.a){
		return a.time<b.time;
	}
	else{
		return false;
	}	
}

int main()
{
	int n, m;
	edg info[100002];
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++){
		scanf("%d", &info[i].time);
	}
	sort(info+1, info+n, comp);
	for(int i=1; i<=m; i++){
		if(i==m){
			for(int j=1; j<=m; j++){
				info[j].a+=info[j].time;
			}
		}
		info[1].a+=info[i].time;
		sort(info+1, info+n+1, comp);		
	}
	printf("%lld", info[1].a);
}
