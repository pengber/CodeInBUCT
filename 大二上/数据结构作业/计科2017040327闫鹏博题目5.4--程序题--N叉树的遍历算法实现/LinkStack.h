/************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/20
**************************************************************/
/***********************************************************
*Problem	:
			1.traverse()函数未定义
*Tips:		:

*************************************************************/
/************************************************************
*History	:

*************************************************************/

#ifndef LINKSTACK_H_INCLUDE
#define LINKSTACK_H_INCLUDE

#include <iostream>
#include "Node.h"
//#define DEBUG
//#define REMIND							//输出提示信息将这条语句打开

template <class ElemType>
class LinkStack {
/********************************公共接口**********************************/
public:
//基本成员函数:
	LinkStack();

	virtual ~LinkStack();
//特征函数:
	int getLength() const;

	bool getTopElem(ElemType & elem) const;

	//判
	bool isEmpty() const;

	//插
	bool push(const ElemType & elem);

	//改
	//无

	//删
	bool pop(ElemType & elem);

	void clean();
//特殊函数
	void display() const;

	void traverse(void(*visit)(const ElemType &)) const;
//重载函数
	//LinkStack<ElemType> & operator(const LinkStack<ElemType> & copy);
/*================================公共接口声明完毕==============================*/
protected:
	Node<ElemType> * top;
};
/*******************************基本成员函数实现*********************************/
template <class ElemType>
LinkStack<ElemType>::LinkStack() {
	top = NULL;
}
template <class ElemType>
LinkStack<ElemType>::~LinkStack() {
	this->clean();
}
/*==============================基本成员函数实现完毕==============================*/
/*******************************基本成员函数实现*********************************/
//函数名称: int getLength() const
//函数功能: 返回链表长度
//无子函数
template <class ElemType>
int LinkStack<ElemType>::getLength() const {
	Node<ElemType> * tempPtr;
	tempPtr = top;
	int length = 0;

	while (tempPtr != NULL) {
		length++;
		tempPtr = tempPtr->next;
	}

	return length;
}
//函数名称: bool getTopElem(ElemType & elem) const
//函数功能: 返回栈顶首元素
template <class ElemType>
bool LinkStack<ElemType>::getTopElem(ElemType & elem) const {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "链栈为空,无法查询栈顶元素" << endl;
#endif
		return false;
	}
	else {
		elem = top->data;
		return true;
	}
}
//函数名称: bool isEmpty() const
//函数功能: 判断链表是否为空,空则返回1,为空返回0
template <class ElemType>
bool LinkStack<ElemType>::isEmpty() const {
	return top == NULL;
}
//函数名称: bool push(const ElemType & elem)
//函数功能: 进行push操作
//无子函数
//注意事项: 将第一个元素当成普通元素就行
template <class ElemType>
bool LinkStack<ElemType>::push(const ElemType & elem) {
	Node<ElemType> * tempPtr;
	
	tempPtr = new Node<ElemType>(elem, top);
	top = tempPtr;
	return true;

}
//函数名称: bool pop(ElemType & elem)
//函数功能: 进行pop操作,值由引用调用得回
template <class ElemType>
bool LinkStack<ElemType>::pop(ElemType & elem) {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "链表为空,不能进行pop操作" << std::endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempPtr;

		tempPtr = top;
		elem = top->data;
		top = top->next;
		delete tempPtr;
		return true;
	}
}
//函数名称: ElemType pop();
//函数功能: 进行pop操作,值由返回值带出
//无子函数:
//注意事项: 此函数是为符合用户习惯设立
template <class ElemType>
ElemType pop() {
	Node<ElemType> * tempPtr;
	ElemType elem;

	tempPtr = top;
	elem = top->data;
	top = top->next;
	delete tempPtr;
	return elem;
}
//函数名称: void clean()
//函数功能: 将链栈清空
//其子函数: bool pop();
template <class ElemType>
void LinkStack<ElemType>::clean() {
	ElemType tempElem;

	while (top != NULL) {
		this->pop(tempElem);
	}
}
//函数名称: void display()
//函数功能: 显示栈内元素
template <class ElemType>
void LinkStack<ElemType>::display() const {
	Node<ElemType> * tempPtr;
	tempPtr = top;
	while (tempPtr != NULL) {
		cout << tempPtr->data << endl;
		tempPtr = tempPtr->next;
	}
}
/*================================公共接口声明完毕==============================*/
#endif