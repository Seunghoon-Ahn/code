#include <iostream>

using namespace std;

int paper[128][128] = {0};
int totalsize = 0;
int cnt[2] = {0, 0};

int checkpaper(int x, int y, int size);
void color(int x, int y, int size);

void color(int x, int y, int size) {
	int mid = size / 2;

	if(checkpaper(x, y, size) == 0) {
		color(x, y, mid);
		color(x+mid, y, mid);
		color(x, y+mid, mid);
		color(x+mid, y+mid, mid);
	}
	else {
		if(size == totalsize) cnt[paper[0][0]]++;
		else ;
	}
}


int main(void) {

	cin>>totalsize;
	
	for(int i = 0; i < totalsize; ++i) {
		for(int j = 0; j < totalsize; ++j) {
			cin>>paper[i][j];
		}
	}

	color(0, 0, totalsize);
	cout<<cnt[0]<<endl<<cnt[1]<<endl;
	
	return 0;
}

int checkpaper(int x, int y, int size) {
	int tmp = 0;

	for( int i = x; i < x + size; ++i)
		for(int j = y; j < y + size; ++j)
			if(paper[x][y] != paper[i][j]) 
				tmp++;

	if(tmp == 0) {
		cnt[paper[x][y]]++;
		return 1;
	}
	else return 0;
}
