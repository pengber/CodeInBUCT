#include "Calculator.h"
#include <ostream>

int main() {
	cout << "请输入中缀表达式,形如3+2=" << endl;

	Calculator<int> calculatorA;
	calculatorA.run();

	return 0;
}