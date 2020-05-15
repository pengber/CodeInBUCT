#include "SqStack.h"
using namespace std;

void pri(int n) {
	cout << n << endl;
}

int main() {
	SqStack<int> stackA(10);
	for (int i = 1; i <= 10; i++) {
		stackA.push(i);
	}
	cout << "长度是: " << endl;
	cout << stackA.getLength() << endl;

	int tempElem;
	stackA.getTopElem(tempElem);
	cout << tempElem << endl;

	if (stackA.isEmpty()) cout << "空" << endl;
	else cout << "非空" << endl;

	if (stackA.isFull()) cout << "满" << endl;
	else cout << "非满" << endl;

	stackA.pop(tempElem);
	cout << tempElem << endl;
	cout << stackA.getLength() << endl;
	stackA.getTopElem(tempElem);
	cout << tempElem << endl;
	cout << "****************分割线**************" << endl;

	SqStack<int> stackB(stackA);
	stackB.display();
	return 0;
}