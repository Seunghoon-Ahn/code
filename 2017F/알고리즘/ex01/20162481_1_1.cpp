#include <iostream>
#include <cmath>
#include <cstdio>
#define ERROR 1e-10

using namespace std;

double x, y, c;

double equation(double low, double high) {
	double mid = (low + high) / 2.0;
	double res = (c / sqrt(x*x - mid*mid)) + ( c / sqrt(y*y - mid*mid)) - 1.0;

	if(low > high) return 0;
	else {
		if(res > ERROR) 
			return equation(low, mid);
		else if(-ERROR < res && res < ERROR) 
			return mid;
		else 
			return equation(mid, high);
	}
}

int main(void) {
	double res;
	double low = 0, high;

	cin>>x>>y>>c;

	high = min(x, y);
	res = equation(low, high);
	printf("%.3lf", res);
	return 0;
}
