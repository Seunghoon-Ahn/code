#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>


using namespace std;

int n,m;
int b[101];
int visited[101];
vector<vector<int> > node;

int dfs(int here){
	if(visited[here]) return 0; 
	visited[here]=1;
	for(int i=0; i<node[here].size(); i++){
		int there = node[here][i];
		if(!b[there]||dfs(b[there])){
			b[there]=here;
			return 1;
		}
	}
	return 0;
}

int bmatch(){
	int result=0;
	for(int i=1; i<=n; i++){
		memset(visited, 0, sizeof(visited));
		if(dfs(i)) result++;
	}
	return result;
}

int main(){
	scanf("%d %d", &n, &m);
	node.resize(n+1);
	for(int i=1; i<=m; i++){
		int a,bb;
		scanf("%d %d", &a, &bb);
		node[a].push_back(bb);
	}	
	printf("%d\n", bmatch());
}
