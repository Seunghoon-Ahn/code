#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

#define NMAX 100
#define MMAX 5000

using namespace std;
int n, m, res;
int match[NMAX];//match[i] : i��° ��Ʈ�Ͽ� ��Ī�� ���
bool isVis[NMAX];//�湮����
vector<int>v[NMAX];

bool dfs(int loc) {
	//cout << loc << endl;
	if (isVis[loc])
		return false;
	isVis[loc] = true;
	for (int target : v[loc]) {
		if (match[target] == -1) {//���� �ش� ��Ʈ�ϰ� ��Ī�� ����� ������
			match[target] = loc;//��Ī������
			res++;//��ĪȽ������
			return true;
		}
	}
	for (int target : v[loc]) {
		if (match[target] != -1 
			&& dfs(match[target])) {//���� �ش� ��Ʈ���� �ٸ� ����� ��Ī �����ϸ�
			match[target] = loc;//�����, Ƚ���� ������Ű�� ����
			return true;
		}
	}
	return false;
}

void matching() {
	fill(match, match + n, -1);
	for (int i = 0; i < n; i++) {
		fill(isVis, isVis + n, false);
		dfs(i);
	}
	return;
}

int main() {
	int a, b, temp;
	cin >> n >> m;
	temp = m;
	while (temp--) {
		cin >> a >> b;
		--a; --b;//1���� �����ϴ°� 0���ͷ� ������
		v[a].push_back(b);//a���� b�ΰ��� edge
	}
	matching();
	cout << res << endl;
	return 0;
}