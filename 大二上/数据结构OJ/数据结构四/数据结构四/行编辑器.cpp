#include <iostream>
using namespace std;
template <class ElemType>
class SqStack {
public:
	SqStack(int capacity = 1000);
	virtual ~SqStack();
	bool push(const ElemType & elem);
	bool pop(ElemType & elem);
	int getLength() const;
	void display() const;
	void clean();
protected:
	ElemType * elems;
	int top;
};

int main() {
	SqStack<char> stack;
	char ch;
	char tempCh;
	ch = getchar();

	while (ch != EOF) {
		while (ch != EOF && ch != '\n') {
			if (ch == '#') {
				stack.pop(tempCh);
			}
			else if (ch == '@') {
				stack.clean();
			}
			else {
				stack.push(ch);
			}
			ch = getchar();
		}
		stack.display();
		stack.clean();
		ch = getchar();
	}
	return 0;
}
template <class ElemType>
SqStack<ElemType>::SqStack(int capacity) {
	elems = new ElemType[capacity];
	top = -1;
}
template <class ElemType>
SqStack<ElemType>::~SqStack() {
	delete[] elems;
}
template <class ElemType>
bool SqStack<ElemType>::push(const ElemType & elem) {
	elems[++top] = elem;
	return true;
}
template <class ElemType>
bool SqStack<ElemType>::pop(ElemType & elem) {
	elem = elems[top--];
	return true;
}
template <class ElemType>
int SqStack<ElemType>::getLength() const {
	int length;
	length = top + 1;
	return length;
}
template <class ElemType>
void SqStack<ElemType>::display() const {
	int current = 0;
	while (current <= top) {
		cout << elems[current++];
	}
	cout << endl;
}
template <class ElemType>
void SqStack<ElemType>::clean() {
	char tempCh;

	while (top != -1) {
		this->pop(tempCh);
	}
}