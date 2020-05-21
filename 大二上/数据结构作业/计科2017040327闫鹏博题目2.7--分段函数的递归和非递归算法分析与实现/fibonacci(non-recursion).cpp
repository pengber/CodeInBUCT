#include <iostream>
using namespace std;

int main() {
	long first, second, third, number;

	cout << "当x = 1 或 x = 0 时,f(x) = 1" << endl;
	cout << "当x >= 2 时,f(x) = f(x-1) + f(x-2)" << endl;
	cout << "请输入自变量的值" << endl;
	
	first = 1;
	second = 1;
	third = 0;

	cin >> number;
	for (int i = 2; i <= number; i++) {	//i=2是因为循环number-1即可,从f(2)算起
		third = first + second;
		first = second;
		second = third;
	}

	cout << "函数值为" << third << endl;
	return 0;
}