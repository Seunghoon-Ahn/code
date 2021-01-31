#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct edg{
	int idx;
	int dst;
	bool operator <(edg A)const {return dst>A.dst;}
};

vector<edg> gph[1002];
int dst[1002];

int main()
{
	int n,m;
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++){
		int a, b,c;
		scanf("%d %d %d", &a, &b, &c);
		gph[a].push_back({b,c});
	}
	int start, end;
	scanf("%d %d", &start, &end);
	for(int i=0; i<=n; i++){
		dst[i]=1e9;
	}
	dst[start]=0;
	priority_queue<edg> pq;
	pq.push({start,0});
	while(!pq.empty()){
		edg now = pq.top();
		pq.pop();
		if(dst[now.idx]<now.dst) continue;
		for(int i=0; i<gph[now.idx].size(); i++){
			edg nxt= gph[now.idx][i];
			if(dst[nxt.idx]>dst[now.idx]+nxt.dst){
				dst[nxt.idx]=dst[now.idx]+nxt.dst;
				pq.push({nxt.idx, dst[nxt.idx]});
			}
		}
	}
	printf("%d\n", dst[end]);
	return 0;
}
