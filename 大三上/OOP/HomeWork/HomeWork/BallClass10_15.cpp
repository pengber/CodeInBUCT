#include <iostream>
using namespace std;

class Ball {
private:
	double radius;
public:
	Ball();	//默认构造函数
	Ball(const double& r);//以球体半径为构造函数
	Ball(const Ball & b);//拷贝构造函数
	double getRadius() const;
	void enlargeRadius(const int& m);//扩大原来的m倍
	double getArea() const;
	double getVolume() const;
};

Ball::Ball() {
	this->radius = 0;
}
Ball::Ball(const double& r) {
	this->radius = r;
}
Ball::Ball(const Ball& b) {
	this->radius = b.getRadius();
}
double Ball::getRadius() const {
	return this->radius;
}
void Ball::enlargeRadius(const int & m) {
	this->radius += (m * radius);
}
double Ball::getArea() const {
	return 4 * 3.14 * this->radius * this->radius;
}
double Ball :: getVolume() const {
	return 1.0 * 4 / 3 * 3.14 * radius * radius * radius;
}

int main() {
	cout << "请输入构造的球体半径:" << endl;
	double r;
	cin >> r;
	Ball A(r);
	cout << "A的表面积为" << A.getArea() << ",A的体积为" << A.getVolume() << endl;
	Ball B(A);
	cout << "B的半径为A的半径扩大1倍" << endl;
	B.enlargeRadius(1);
	cout << "B的表面积为" << B.getArea() << ",B的体积为" << B.getVolume() << endl;
	system("pause");

	return 0;
}