#include "SqStack.h"
using namespace std;
void menu();

int main() {
	int opeNum;
	int memNum;
	int tempElem;
	menu();
	SqStack<int> stackA;
	while (cout << "请输入操作数:" && cin >> opeNum) {
		switch (opeNum) {
		case 1:
			cout << "请输入栈内元素数目" << endl;
			cin >> memNum;
			cout << "请输入栈内元素,由栈底到栈顶" << endl;
			for (int i = 1; i <= memNum; i++) {
				cin >> tempElem;
				stackA.push(tempElem);
			}
			break;
		case 2:
			cout << "请输入要入栈元素:";
			cin >> tempElem;
			stackA.push(tempElem);
			break;
		case 3:
			stackA.pop(tempElem);
			cout << "已将栈顶元素" << tempElem << endl;
			break;
		case 4:
			if (stackA.isEmpty()) cout << "栈空" << endl;
			else cout << "栈非空" << endl;
			break;
		case 5:
			if (stackA.isFull()) cout << "栈满" << endl;
			else cout << "栈非满" << endl;
			break;
		case 6:
			stackA.clean();
			break;
		case 7:
			stackA.display();
			break;
		}
	}

	return 0;
}

void menu() {
	cout << "********************线性栈操作菜单****************************" << endl;
	cout << "1.建立线性栈" << endl;
	cout << "2.入栈" << endl;
	cout << "3.出栈" << endl;
	cout << "4.判断栈是否为空" << endl;
	cout << "5.判断栈是否为满" << endl;
	cout << "6.将栈清空" << endl;
	cout << "7.由栈底到栈顶显示栈内元素" << endl;
}