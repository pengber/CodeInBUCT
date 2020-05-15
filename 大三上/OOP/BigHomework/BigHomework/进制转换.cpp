#include "SqStack.h"
using namespace std;

int main() {
	SqStack<int> stackA;
	int tarSystem, souNum, quo, rem;
	int tempCase;
	
	cout << "请输入十进制数" << endl;
	cin >> souNum;
	cout << "你想将十进制转换成几进制?只能转成2/8/16进制" << endl;
	cin >> tarSystem;

	quo = souNum;
	while (quo != 0) {
		rem = quo % tarSystem;
		quo = quo / tarSystem;
		stackA.push(rem);
	}

	cout << "将10进制" << souNum << "转为" << tarSystem << "进制结果为:";
	while (stackA.getLength() != 0) {
		stackA.pop(tempCase);
		switch (tempCase) {
			case 10:
				cout << "A";
				break;
			case 11:
				cout << "B";
				break;
			case 12:
				cout << "C";
				break;
			case 13:
				cout << "D";
				break;
			case 14:
				cout << "E";
				break;
			case 15:
				cout << "F";
				break;
			default:
				cout << tempCase;
		}
	}
	
	return 0;
}