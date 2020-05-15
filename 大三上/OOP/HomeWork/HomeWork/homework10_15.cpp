#include <iostream>
using namespace std;

class Rectangle {
private:
	int r_long;
	int r_width;
public:
	Rectangle();
	Rectangle(const int& l, const int& w);//不改变引用变量用const修饰
	int get_long() const;//以下成员函数均不改变对象所以用const修饰
	int get_width() const;
	int comp_area() const;
	int comp_perimeter() const;
};

Rectangle::Rectangle() {
	this->r_long = 0;
	this->r_width = 0;
}

Rectangle::Rectangle(const int& l, const int& w) {
	this->r_long = l;
	this->r_width = w;
}

int Rectangle::get_long() const {
	return this->r_long;
}

int Rectangle::get_width() const {
	return this->r_width;
}

int Rectangle::comp_area() const {
	return this->r_long * this->r_width;
}

int Rectangle::comp_perimeter() const {
	return 2 * (this->r_long + this->r_width);
}
int main() {
	Rectangle A;
	int a, b;
	cout << "请输入构造B的长和宽：" << endl;
	cin >> a >> b;
	Rectangle B(a, b);
	cout << "A的长为" << A.get_long() << ",A的宽为" << A.get_width() << endl;
	cout << "B的长为" << B.get_long() << ",B的宽为" << B.get_width() << endl;
	cout << "A的面积为" << A.comp_area() << endl;
	cout << "B的周长为" << B.comp_perimeter() << endl;

	system("pause");
	return 0;
}