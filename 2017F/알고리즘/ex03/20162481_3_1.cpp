//19계단 refrigerator
#include <iostream>
using namespace std;
void sort(int arr[100001][2], int s, int e);

int main(void) {
	int N = 0;
	int ref = 1, h = 0, temp = 0;
	int icecream[100001][2] = {0};
	int min = 0, mini = 0, max = 0;

	cin>>N;
	for(int i = 1; i <= N; i++) 
		cin>>icecream[i][0]>>icecream[i][1];

	sort(icecream, 1, N);

	max = icecream[1][1];

	for( h = 1; h <= N; h++) {
		if(max < icecream[h][0]) {
			ref++;
			max = icecream[h][1];
		}
	}
	cout<<ref;
	return 0;
}

void sort(int arr[100001][2], int left, int right) {
	int sleft = left;
	int sright = right;
	int pivot = arr[left][1];
	int pivot0 = arr[left][0];

	while(left < right) {
		while((arr[right][1] >= pivot) && (left < right))
			right--;

		if(left != right) {
			arr[left][1] = arr[right][1];
			arr[left][0] = arr[right][0];
		}

		while((arr[left][1] <= pivot) && (left < right))
			left++;

		if(left != right) {
			arr[right][1] = arr[left][1];
			arr[right][0] = arr[left][0];
			right--;
		}
	}
	arr[left][1] = pivot;
	arr[left][0] = pivot0;
	pivot = left;
	left = sleft;
	right = sright;

	if(left < pivot) sort(arr, left, pivot-1);
	if(right > pivot) sort(arr, pivot+1, right);
}
