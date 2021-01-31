#include <iostream>
using namespace std;
const int MN = 27;
char L[MN], R[MN];

void Pre(char n) {
	printf("%c", n);
	if(L[n-'A'] != '.')
		Pre(L[n-'A']);
	if(R[n-'A'] != '.')
		Pre(R[n-'A']);
}

void In(char n) {
	if(L[n-'A'] != '.')
		In(L[n-'A']);
	printf("%c", n);
	if(R[n-'A'] != '.')
		In(R[n-'A']);
}

void Post(char n) {
	if(L[n-'A'] != '.')
		Post(L[n-'A']);
	if(R[n-'A'] != '.')
		Post(R[n-'A']);
	printf("%c", n);
}

int main() {
	int N;  cin >> N;
	for(int i = 0; i < N; i++) {
		char a, b, c;   cin >> a >> b >> c;
		L[a-'A'] = b;
		R[a-'A'] = c;
	}
	Pre('A');
	printf("\n");
	In('A');
	printf("\n");
	Post('A');
}
