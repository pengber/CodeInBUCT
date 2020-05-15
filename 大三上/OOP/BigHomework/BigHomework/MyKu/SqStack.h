/************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/20 
************************************************************************************/
/************************************************************************************
*Problem	:
			1.复制构造函数未定义
*Tips:		:
			1.初始时栈底和栈顶都指向-1;入栈时++top
			2.默认栈顶指针指向栈顶首元素 
************************************************************************************/
/************************************************************************************
*History	:

************************************************************************************/
#ifndef SQSTACK_H_INCLUDE
#define SQSTACK_H_INCLUDE

#include <iostream>
//#define DEBUG
//#define REMIND

template <class ElemType>
class SqStack {
public:
//基本成员函数
	SqStack(int capacity = 100);
	//SqStack(const SqStack & copy);
	virtual ~SqStack();
//特征函数
	//得
	int getLength() const;

	bool getTopElem(ElemType & elem) const;

	void traverse(void(*visit)(const ElemType &)) const;

	//判
	bool isEmpty() const;

	bool isFull() const;
	//插

	bool push(const ElemType & elem);

	//改
	//无

	//删
	bool pop(ElemType & elem);

	void clean();
//特殊函数
	void display() const;
//重载
	SqStack & operator=(const SqStack & copy);

protected:
	ElemType * elems;

	int top;
	
	int capacity;
};
/*********************************公共接口实现**************************************/
/*******************************基本成员函数实现************************************/
template <class ElemType>
SqStack<ElemType>::SqStack(int capacity) {
	elems = new ElemType[capacity];
	this->capacity = capacity;
	top = -1;
}

template <class ElemType>
SqStack<ElemType>::~SqStack() {
	delete[] elems;
}
/*============================基本成员函数实现完毕==================================*/
/*******************************特征函数实现****************************************/
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
void SqStack<ElemType>::traverse(void(*visit)(const ElemType &)) const {
	for (int i = 0; i <= top; i++) {
		(*visit)(elems[i]);
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
#ifdef REMIND
		std::cout << "已满,不能进行push操作" << std::endl;
#endif
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
/*=============================基本特征实现完毕=====================================*/
/*=============================公共接口实现完毕=====================================*/

#endif
