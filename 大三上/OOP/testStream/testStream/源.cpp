#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class People {
protected:
	int age;
	static int id;
public:
	People(int a) :age(a) {
		id++;
	};
	static int getId() {
		return id;
	}
	static int getAge() {
		return People::age;
	}
};
int People::id = 0;
int main() {
	People first(1);
	cout << first.getId();//验证静态函数成员是否可以通过对象访问：可以。
	cout << People::getId();
	return 0;
}