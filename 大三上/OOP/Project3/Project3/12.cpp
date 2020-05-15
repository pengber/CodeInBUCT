#include <iostream>
using namespace std;
class Complex
{
protected:
	int real;
	int image;
public:
	Complex(int i = 0, int j = 0) :real(i), image(j) {};
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};
std::ostream & operator<<(std::ostream& os,const Complex & c) {
	if (c.image == 0) {
		os << c.real;
		return os;
	}
	else {
		os << c.real << c.image << "i";
		return os;
	}
}
int main()
{
	int i, j;
	std::cin >> i >> j;
	Complex z1(i, j);
	std::cout << z1 << std::endl; //Êä³öz1¶ÔÏó 
	return 0;
}