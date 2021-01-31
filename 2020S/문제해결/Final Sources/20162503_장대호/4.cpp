#include<cstdio>
#include <vector>
#include <queue>
using namespace std;

int visit[301];
int N, M,K;
vector<vector<pair<int, int> > > map;
void dfs(int from, pair<int, int> d,int depth) {
	
	depth++;
	int cur = d.first;
	int w = d.second;
	if (visit[cur] < visit[from] + w)
		visit[cur] = visit[from] + w;
	else
		return;
	for (int i = 0; i < map[cur].size(); i++) {
		if(depth +1 <= M && cur < map[cur][i].first)
			dfs(cur, map[cur][i], depth);
	}
}
int main(void) {
	scanf("%d%d%d", &N, &M,&K);
	map.resize(N + 1);
	for(int i=0;i<K;i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		map[a].push_back(make_pair(b, c));
	}
	for (int i = 0; i < map[1].size(); i++) {
		dfs(1,map[1][i],1);
	}
	printf("%d\n", visit[N]);
}