#include <iostream>
using namespace std;

long fibon(long num) {
	if (num == 0 || num == 1) {
		return 1;
	}
	else {
		return fibon(num - 1) + fibon(num - 2);
	}
}

int main() {
	cout << "当x = 1 或 x = 0 时,f(x) = 1" << endl;
	cout << "当x >= 2 时,f(x) = f(x-1) + f(x-2)" << endl;
	cout << "请输入自变量的值" << endl;
	long number;

	cin >> number;
	cout << "函数值为" << fibon(number) << endl;
	return 0;
}