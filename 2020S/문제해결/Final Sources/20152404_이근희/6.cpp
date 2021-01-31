#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


int arr[102][102];
bool out[102][102];
bool visited[102][102];
struct edg{
	int x,y;
};
const int dx[4]={0, 0, -1, 1};
const int dy[4]={1, -1, 0, 0};

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d", &arr[i][j]);
		}
	}
	queue<edg> q;
	
	int time=0;
	int chk=0;
	while(1){
		chk=0;
		q.push({1,1});
	while(!q.empty()){
		edg now=q.front();
		q.pop();
		for(int i=0; i<4; i++){
			int nx=dx[i]+now.x;
			int ny=dy[i]+now.y;
			if(arr[nx][ny]==1||visited[nx][ny]||nx<=0||ny<=0||nx>n||ny>m) continue;
			visited[nx][ny]=true;
			out[nx][ny]=true;
			q.push({nx,ny});
		}
	}
		memset(visited, 0, sizeof(visited));
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				if(arr[i][j]==1&&!visited[i][j]){
					visited[i][j]=true;
					chk=1;
					int num=0;
					for(int z=0; z<4; z++){
						int nx=dx[z]+i;
						int ny=dy[z]+j;
						if(out[nx][ny])
							num++;
					
					}
					if(num>=2) arr[i][j]=0;
				}
			}
		}
		if(chk==0)
			break;
		time++;
		memset(visited, 0, sizeof(visited));
		memset(out, 0, sizeof(out));
	}
	printf("%d\n", time);
}
