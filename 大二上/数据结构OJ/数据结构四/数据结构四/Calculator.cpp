#include <iostream>
using namespace std;
#define DEBUG
#define REMIND

template <class ElemType>
class SqStack {
public:
	SqStack(int capacity = 100);
	
	int getLength() const;

	bool getTopElem(ElemType & elem) const;

	void traverse(void(*visit)(const ElemType &)) const;
	bool isEmpty() const;

	bool isFull() const;
	bool push(const ElemType & elem);

	bool pop(ElemType & elem);

	void clean();

	void display() const;

protected:
	ElemType * elems;

	int top;

	int capacity;
};
template <class ElemType>
class Calculator {
public:
	Calculator() {};

	//virtual ~Calculaotr() {};

	void run();
protected:
	

	bool isOperator(char & opch);					

	char precedeOpch(char & opchA, char & opchB) const;			

	ElemType compute(ElemType & left, char & opch, ElemType & right) const;

	void popLeftRight(SqStack<ElemType> & opnd, ElemType & left, ElemType & right);

};
template <class ElemType>
bool Calculator<ElemType>::isOperator(char & opch) {
	if (opch == '+' || opch == '-' || opch == '*' || opch == '/' || opch == '%'
		|| opch == '#' || opch == '(' || opch == ')' || opch == '^') return true;
	else
		return false;
}
template <class ElemType>
char Calculator<ElemType>::precedeOpch(char & opchA, char & opchB) const {
	if (opchA == '+' || opchB == '-') {
		if (opchB == '+' || opchB == '-' || opchB == ')' || opchB == '#') {
			return '>';
		}
		else {
			return '<';
		}
	}
	else if (opchA == '*' || opchA == '/') {
		if (opchB == '(') {
			return '<';
		}
		else {
			return '>';
		}
	}
	else if (opchA == '(') {
		if (opchB == ')') {
			return '=';
		}
		else if (opchB == '#') {
			return 'e';
		}
		else {
			return '<';
		}
	}
	else if (opchA == ')') {
		if (opchB == '(') {
			return 'e';
		}
		else {
			return '>';
		}
	}
	else if (opchA == '#') {
		if (opchB == ')') {
			return 'e';
		}
		else if (opchB == '#') {
			return '=';
		}
		else {
			return '<';
		}
	}
}
template <class ElemType>
ElemType Calculator<ElemType>::compute(ElemType & left, char & opch, ElemType & right) const {
	if (opch == '+') {
		return left + right;
	}
	else if (opch == '-') {
		return left - right;
	}
	else if (opch == '*') {
		return left * right;
	}
	else if (opch == '/') {
		return left / right;
	}
}
template <class ElemType>
void Calculator<ElemType>::popLeftRight(SqStack<ElemType> & opnd, ElemType & left, ElemType & right) {

	opnd.pop(right);
	opnd.pop(left);
}
template <class ElemType>
void Calculator<ElemType>::run() {
	SqStack<int> opnd(100);
	SqStack<char> optr(100);
	char optrTop, ch;
	char theta;
	int operand;

	optr.push('#');
	cin >> ch;
	while ((optr.getTopElem(optrTop), optrTop != '#') || ch != '#') {
		if (!isOperator(ch)) {
			cin.putback(ch);
			cin >> operand;
			opnd.push(operand);
			cin >> ch;
		}
		else {
			switch (precedeOpch(optrTop, ch)) {
			case '>':
				int left, right;
				popLeftRight(opnd, left, right);
				optr.pop(theta);
				opnd.push(compute(left, theta, right));
				break;
			case '<':
				optr.push(ch);
				cin >> ch;
				break;
			case '=':
				optr.pop(optrTop);
				cin >> ch;
				break;
			case 'e':
				cout << "error!" << endl;
				exit(2);
			}
		}
	}
	opnd.getTopElem(operand);
	cout << operand << endl;
}
int main() {
	Calculator<int> calculatorA;
	calculatorA.run();

	return 0;
}
template <class ElemType>
SqStack<ElemType>::SqStack(int capacity) {
	elems = new ElemType[capacity];
	this->capacity = capacity;
	top = -1;
}
template <class ElemType>
int SqStack<ElemType>::getLength() const {
	return top + 1;
}
template <class ElemType>
bool SqStack<ElemType>::getTopElem(ElemType & elem) const {
	if (top == -1) {
		return false;
	}
	else {
		elem = elems[top];
		return true;
	}
}
template <class ElemType>
bool SqStack<ElemType>::isEmpty() const {
	return top == -1;
}
template <class ElemType>
bool SqStack<ElemType>::isFull() const {
	return top + 1 == capacity;
}
template <class ElemType>
bool SqStack<ElemType>::push(const ElemType & elem) {
	if (this->isFull()) {
		return false;
	}
	else {
		elems[++top] = elem;
		return true;
	}
}
template <class ElemType>
bool SqStack<ElemType>::pop(ElemType & elem) {
	if (this->isEmpty()) {
		return false;
	}
	else {
		elem = elems[top--];
		return true;
	}
}
template <class ElemType>
void SqStack<ElemType>::clean() {
	top = -1;
}
template <class ElemType>
void SqStack<ElemType>::display() const {
	for (int i = 0; i <= top; i++) {
		std::cout << elems[i] << std::endl;
	}
}