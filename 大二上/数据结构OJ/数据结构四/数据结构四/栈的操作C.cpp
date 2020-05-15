#include <iostream>
#include <string>
#include "stdio.h"
using namespace std;

class SqStack {
protected:
	int * elems;
	int capacity;
	int top;

public:
	SqStack(int capacity = 100);
	virtual ~SqStack();
	bool isEmpty() const;
	bool pop(int & elem);
	bool push(const int & elem);
	void clean();
	void traverse(void(*visit)(int &));
};
SqStack::SqStack(int capacity) {
	this->capacity = capacity + 1;
	this->top = -1;
	this->elems = new int[capacity];
}
SqStack::~SqStack() {
	delete[] elems;
}
bool SqStack::isEmpty() const {
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}
bool SqStack::pop(int & elem) {
	if (this->isEmpty()) {
		return false;
	}
	else {
		elem = elems[top--];
		return true;
	}
}
bool SqStack::push(const int & elem){
	if (capacity - 1 == top) {
		return false;
	}
	else {
		elems[++top] = elem;
		return true;
	}
}
void SqStack::clean() {
	top = -1;
}
void SqStack::traverse(void(*visit)(int &)) {
	for (int i = 0; i <= top; i++) {
		(*visit)(elems[i]);
	}
}
int main() {
	char ch;
	SqStack stack(1001);
	int i = 1;
	int tempElem;
	while (ch = getchar()) {
		//while (cin >> ch) {
			switch (ch)
			{
			case 'P':
				if (stack.push(i++));
				else {
					cout << "error";
					cout << endl;
					while (ch = getchar() != '\n');
				}
				break;
			case 'Q':
				if (stack.pop(tempElem))
					cout << tempElem << " ";
				else {
					cout << "error";
					cout << endl;
					stack.clean();
					i = 1;
					while (ch = getchar() != '\n');					
				}
				break;
			case '\n':
				cout << '\n';
				i = 1;
				stack.clean();
				break;
			default:
				break;
			}
		//}
	}
	return 0;
}