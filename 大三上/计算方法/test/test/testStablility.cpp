#include <iostream>
#include <iomanip>
using namespace std;
double f(double x, int n) {
	return double(1.0/ n) - 5.0 * x;
}
double f2(double x1, int n) {
	return 1.0/ (5 * n) - 1.0 * x1/5;
}
int main() {
	int i;	
	double x0, x1;
	x0 = 0.1823;
	for (i = 1; i < 20; i++) {
		x1 = f(x0, i);
		cout << "x" << i << ":" <<x1 << endl;
		x0 = x1;
	}
	cout << endl;
	x1 = 0.0203;
	for (int i = 7; i > 0; i--) {
		x0 = f2(x1, i);
		cout << "x" << i << ":" << x0 << endl;
		x1 = x0;
	}
	cout << setprecision(20) << 1.0 *22 / 7 << endl;
	return 0;
}