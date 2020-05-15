#include <iostream>
#include <iomanip>

using namespace std;

class Circle {
private:
	int radius;
public:
	Circle(int r = 1);
	double area();
};

Circle::Circle(int r) {
	this->radius = r;
}
double Circle::area() {
	return 3.14 * radius * radius;
}
int main()
{
	Circle c1;
	cout << setiosflags(ios::fixed) << setprecision(2) << c1.area() << endl;
	//输出要求小数点后必须保留2位有效数字（四舍五入），不足补零 
	cout << setiosflags(ios::fixed) << setprecision(2) << c1.area() << endl;
	int a;
	cin >> a;
	Circle c2(a);
	cout << setiosflags(ios::fixed) << setprecision(2) << c2.area() << endl;
	return 0;
}