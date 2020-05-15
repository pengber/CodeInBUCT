//验证平台命名空间和编译器命名空间的不同

#include <iostream>
using namespace std;

class Complex {
protected:
	int real;
	int image;
public:
	Complex(int i, int j) :real(i), image(j) {};
	friend ostream& operator <<(ostream& os, const Complex& a);
};

ostream& operator <<(ostream& os, const Complex& a) {

}