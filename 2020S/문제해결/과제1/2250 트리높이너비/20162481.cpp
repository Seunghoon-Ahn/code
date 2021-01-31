#include <iostream>
#include <algorithm>
using namespace std;

typedef struct node *pnode;
typedef struct node {
	int data;
	pnode left, right;
} node;

node nodearr[10004];
int numarr[10004];
int levelarr[10004];
int nodearrpointer = 0;
int lv = 1;

//중위탐색 함수
void search(pnode node) {
	if (node) {
		if(node->left) search(node->left);
		numarr[nodearrpointer] = node->data;
		nodearrpointer++;
		if(node->right) search(node->right);
	}
}

//레벨 계산하는 함수
int flevel(pnode node, pnode findingnode, int level) {
	if (node == NULL) return 0;
	if (node == findingnode) return level;
	if (node->left == NULL && node->right == NULL) return 0;

	int leftlv = flevel(node->left, findingnode, level+1);
	int rightlv = flevel(node->right, findingnode, level+1);
	
	if (!leftlv) return rightlv;
	else return leftlv;
}

int main(void) {
	int num;
	int nodenum, nodeleft, noderight;

	cin >> num;

	for (int i = 1; i <= num; i++) {
		nodearr[i].data = i;
		nodearr[i].left = NULL;
		nodearr[i].right = NULL;
	}

	int tmpnum = 0;

	for (int i = 1; i <= num; i++) {
		cin >> nodenum >> nodeleft >> noderight;
		if (i == 1) tmpnum = nodenum;
		nodearr[nodenum].data = nodenum;
		if(nodeleft != -1)	nodearr[nodenum].left = &nodearr[nodeleft];
		if(noderight != -1) nodearr[nodenum].right = &nodearr[noderight];
	}

	search(&nodearr[tmpnum]);

	//레벨 구하기
	for(int i = 0; i < num; i++) {
		levelarr[i] = flevel(&nodearr[tmpnum], &nodearr[numarr[i]], lv);
	}

	int maxlevel, widelevel = 1;
	int width = 1;
	int findloc1, findloc2 = 0;
	maxlevel = *max_element(levelarr, levelarr + num);

	for (int i = 1; i <= maxlevel; i++) {
		if (maxlevel == 1) widelevel = 1;
		else {
			for (int j = 0; j < num; j++) {
				if (levelarr[j] != i) continue;
				else {
					findloc1 = j;
					break;
				}
			}
			for (int j = num - 1; j >= 0; j--) {
				if (levelarr[j] != i) continue;
				else {
					findloc2 = j;
					break;
				}
			}
			if ((findloc2 - findloc1) + 1 > width) {
				widelevel = i;
				width = findloc2 - findloc1 + 1;
			}
		}
	}
	cout << widelevel << ' ' << width << '\n';
	return 0;
}