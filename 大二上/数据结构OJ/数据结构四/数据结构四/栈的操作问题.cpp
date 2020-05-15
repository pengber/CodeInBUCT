#include <iostream>
using namespace std;
/*-----------stack-----------------*/
class SqStack {
protected:
	int * elems;
	int capacity;
	int top;
public:
	SqStack(int capacity = 1110);
	bool pop(int & elem);
	bool push(const int & elem);
	bool isEmpty();
	int getLength();
	bool getTopElem(int & elem) const;
	void display();
};
SqStack::SqStack(int capacity) {
	this->capacity = capacity;
	elems = new int[capacity];
	top = -1;
}
bool SqStack::pop(int & elem) {
	if (top == -1) {
		return false;
	}
	else {
		elem = elems[top--];
		return true;
	}
}
bool SqStack::push(const int & elem) {
	if (top == capacity - 1) {
		cout << "Stack id full!" << endl;
		return false;
	}
	else {
		elems[++top] = elem;
		return true;
	}
}
bool SqStack::isEmpty() {
	if (top == -1)
		return true;
	else
		return false;
}
int SqStack::getLength() {
	return top + 1;
}
bool SqStack::getTopElem(int & elem) const {
	if (top == -1) {
		return false;
	}
	else {
		elem = elems[top];
		return true;
	}
}
void SqStack::display() {
	if (top == -1) {
		cout << "Stack is empty!" << endl;
	}
	for (int i = 0; i <= top; i++) {
		cout << elems[i];
	}
}
/*===============stack over=============*/
int main() {
	SqStack stack;
	int n;
	int target[1001];
	int tempElem;
	stack.push(0);							//这一条应该在while外面,是每次测试数据的初始条件
	while (cin >> n) {
		int j = 0;							//每次测试数据应该都将j = 0;即traget应该从0位置比较;				
		for (int i = 0; i < n; i++) {
			cin >> target[i];
		}
		for (int i = 1; i <= n || stack.getLength() != 1;) {
			stack.getTopElem(tempElem);
			if (tempElem < target[j]) {
				cout << 'P';
				stack.push(i++);			//当push后才+i;
				continue;
			}
			stack.pop(tempElem);
			if (tempElem == target[j]) {
				j++;
				cout << 'Q';
				continue;
			}
			else {
				cout << " error";
				break;
			}
		}
		cout << endl;
		for (int i = 0; i < 1002; i++) {			//每组测试数据初始环境应该为0
			target[i] = 0;
		}
	}
	

	return 0;
}