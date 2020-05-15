#include <iostream>
using namespace std;

class SqStack {
public:
	SqStack(int capacity = 100);
	bool push(const int & elem);
	bool pop(int & elem);
	int getLength() const;
	void display() const;
protected:
	int * elems;

	int top;
};

int main() {
	SqStack stackA;
	int tarSystem = 8, souNum, quo, rem;
	int tempCase;

	while (cin >> souNum) {
		quo = souNum;
		while (quo != 0) {
			rem = quo % tarSystem;
			quo = quo / tarSystem;
			stackA.push(rem);
		}
		while (stackA.getLength() != 0) {
			stackA.pop(tempCase);
			cout << tempCase;
		}
		cout << endl;
	}
	
	return 0;
}
SqStack::SqStack(int capacity) {
	elems = new int[capacity];
	top = -1;
}
bool SqStack::push(const int & elem) {
	elems[++top] = elem;
	return true;
}
bool SqStack::pop(int & elem) {
	elem = elems[top--];
	return true;
}
int SqStack::getLength() const {
	int length;
	length = top + 1;
	return length;
}
void SqStack::display() const {
	int current = 0;
	while (current <= top) {
		cout << elems[current++];
	}
	cout << endl;
}