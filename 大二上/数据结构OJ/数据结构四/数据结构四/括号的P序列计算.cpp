#include <iostream>
#include <string>
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
	this->capacity = capacity;
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
		cout << "error";
		return false;
	}
	else {
		//cout << 'Q';
		elem = elems[top--];
		return true;
	}
}
bool SqStack::push(const int & elem) {
	if (capacity - 1 == top) {
		cout << "error";
		return false;
	}
	else {
		//cout << 'P';
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

	return 0;
}