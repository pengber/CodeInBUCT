#include <iostream>

using namespace std;

void f(double x1, double x2, double x3, double& y1, double& y2, double &y3) {
	y1 = -0.4 * x2 - 0.2 * x3 - 2.4;
	y2 = 0.25 * x1 - 0.5 * x3 + 5;
	y3 = -0.2 * x1 + 0.3 * x2 + 0.3;
}

int main() {
	double x1, x2, x3, y1, y2, y3;
	y1 = y2 = y3 = 0;
	for (int i = 1; i < 20; i++) {
		x1 = y1;
		x2 = y2;
		x3 = y3;
		f(x1, x2, x3, y1, y2, y3);
		cout << i << " " << y1 << " " << y2 << " " << y3 << endl;
	}
	return 0;
}