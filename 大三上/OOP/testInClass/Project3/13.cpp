#include <iostream>

using namespace std;

class Rectangle {
protected:
	int r_width;
	int r_long;
public:
	Rectangle(){
		r_width = 10;
		r_long = 10;
	};
	Rectangle(int x, int y) {
		r_width = y;
		r_long = x;
	}
	int comp_area() const {
		return r_width * r_long;
	}
	int comp_perimeter()const {
		return 2 * (r_width + r_long);
	}
	int get_width() const {
		return r_width;
	}
	int get_long() const {
		return r_long;
	}
};

int main()
{
	int a, b;
	cin >> a >> b;
	Rectangle rect1, rect2(a, b); //分别调用不同的构造函数，创建两个对象
	cout << "(" << rect1.get_long() << "," << rect1.get_width() << ")" << endl;
	cout << "(" << rect2.get_long() << "," << rect2.get_width() << ")" << endl;
	cout << rect2.comp_area() << endl;
	cout << rect2.comp_perimeter() << endl;
	return 0;
}