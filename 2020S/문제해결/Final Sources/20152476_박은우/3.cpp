#include <cstdio>
#include <vector>
using namespace std;

vector<int> primes;

void eratostes() {
	bool visited[1121] = { 0, };
	visited[0] = 1;
	visited[1] = 1;
	for (int i = 2; i < 35; i++) {
		if (visited[i] == 1) continue;
		primes.push_back(i);
		for (int j = i*i; j < 1121; j += i) {
			visited[j] = 1;
		}
	}
	for (int i = 35; i < 1121; i++) {
		if (visited[i] == 0) primes.push_back(i);
	}
}
int cases;
void makeHab(int cur, int sum, int num, int n, int k) {
	if (sum > n) {
		return;
	}
	if (num > k) {
		return;
	}
	if (sum == n && num == k) {
		cases++;
		return;
	}
	if (primes.size() == cur) return;
	if (primes[cur] > n) return;
	makeHab(cur + 1, sum + primes[cur], num + 1, n, k);
	makeHab(cur + 1, sum, num, n, k);
}
void findHab(int n, int k) {
	cases = 0;
	makeHab(0, 0, 0, n, k);
}
int main() {
	eratostes();
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, k;
		scanf("%d %d", &n, &k);
		findHab(n, k);
		printf("%d\n", cases);
	}
	return 0;
}