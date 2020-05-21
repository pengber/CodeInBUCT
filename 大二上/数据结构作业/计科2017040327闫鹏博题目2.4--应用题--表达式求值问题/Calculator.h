/************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/24
************************************************************************************/
/************************************************************************************
*Problem	:

*Tips:		:
************************************************************************************/
/************************************************************************************
*History	:
************************************************************************************/
#ifndef CALCULATOR_H_INCLUDE
#define CALCULATOR_H_INCLUDE
#include "SqStack.h"
#include <iostream>
using namespace std;
//#define REMIND

template <class ElemType>
class Calculator {
public:
	Calculator() {};

	//virtual ~Calculaotr() {};

	void run();
protected:
	//私有数据成员
	//SqStack<ElemType> opnd;

	//SqStack<char> optr;
	//私有方法成员

	bool isOperator(char & opch);					//opch为操作符

	char precedeOpch(char & opchA, char & opchB) const;			//返回操作符比较的结果

	ElemType compute(ElemType & left, char & opch, ElemType & right) const;//计算结果并返回

	void popLeftRight(SqStack<ElemType> & opnd, ElemType & left, ElemType & right);

};
//函数功能: bool isOperator(char & opch)
template <class ElemType>
bool Calculator<ElemType>::isOperator(char & opch) {
	if (opch == '+' || opch == '-' || opch == '*' || opch == '/' || opch == '%'
		|| opch == '=' || opch == '(' || opch == ')' || opch == '^') return true;
	else
		return false;
}
//函数功能: 返回操作符比较的结果,结果为四种可能: > < = e
template <class ElemType>
char Calculator<ElemType>::precedeOpch(char & opchA, char & opchB) const {
	if (opchA == '+' || opchB == '-') {
		if (opchB == '+' || opchB == '-' || opchB == ')' || opchB == '=') {
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
		else if (opchB == '=') {
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
	else if (opchA == '=') {
		if (opchB == ')') {
			return 'e';
		}
		else if (opchB == '=') {
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
	ElemType tempElem;

	opnd.pop(right);
	opnd.pop(left);
}
/********************************公共接口实现**********************************/
template <class ElemType>
void Calculator<ElemType>::run() {
	SqStack<int> opnd(100);
	SqStack<char> optr(100);
	char optrTop, ch;
	char theta;
	int operand;

	optr.push('=');
	cin >> ch;
	while ((optr.getTopElem(optrTop), optrTop != '=') || ch != '=') {
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
				cout << "符号不匹配!" << endl;
				exit(2);
			}
		}
	}
	opnd.getTopElem(operand);
	cout << "表达式值为" << operand << endl;
}
/*==============================公共接口实现完毕==============================*/
#endif