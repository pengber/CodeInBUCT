#include <iostream>
#include <string>
using namespace std;

class School {
protected:
	string address;
	string header;
public:
	School() {
		address = "";
		header = "";
	}
	School(string a, string h) :address(a), header(h) {}
	void setAddress(string a) {
		address = a;
	}
	string getAddress() const {
		return address;
	}
	void setHeader(string h) {
		header = h;
	}
	string getHeader() const {
		return header;
	}
};

int main()
{
	string a, h;
	cin >> a >> h;
	School s1, s2(a, h); //分别调用不同的构造函数，创建两个对象
	cout << "(" << s1.getAddress() << "," << s1.getHeader() << ")" << endl;
	cout << "(" << s2.getAddress() << "," << s2.getHeader() << ")" << endl;

	cin >> a >> h;
	s1.setAddress(a); //调用成员函数
	s1.setHeader(h); //调用成员函数
	cout << "(" << s1.getAddress() << "," << s1.getHeader() << ")" << endl;
	return 0;
}