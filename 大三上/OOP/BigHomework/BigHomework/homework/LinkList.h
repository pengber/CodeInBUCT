/************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/11/25
**************************************************************************************/
/*************************************************************************************
*Problem	:
*Tips:		:
			1.优化Simple链表,优化各种操作时间复杂度
			2.Node里面的成员m_的前缀,这个LinkList里面有,因为m_是我从未来带来了,但用的旧Node
***************************************************************************************/
/**************************************************************************************
*History	:
**************************************************************************************/
#ifndef LINKLIST_H_INCLUDE
#define LINKLIST_H_INCLUDE
#include <iostream>
#include <stdexcept>
#include "Node.h"

//#define REMIND
template <class ElemType>
class LinkList {
protected:
	Node<ElemType> * m_head;
	int m_length;
	mutable int m_curPos;
	mutable Node<ElemType> * m_curPtr;

public:
	//基本成员函数
	LinkList();
	virtual ~LinkList();
	//特征函数
	//得
	int getLength() const;

	bool getElem(int pos, ElemType & elem) const;

	Node<ElemType> * getCurPtr() const;

	Node<ElemType> * getElemPtr(int pos) const;

	//判

	bool isEmpty() const;

	//增

	bool insertElem(int pos, const ElemType & elem);

	void insertBehindAll(const ElemType & elem);

	//改

	bool setElem(int pos, const ElemType & elem);

	//删
	bool deteleElem(int pos, ElemType & elem);

//特殊函数
	void display() const;
};
/*===============================保护成员函数实现完毕=================================*/
template <class ElemType>
LinkList<ElemType>::LinkList() {
	this->m_length = 0;
	this->m_curPos = 0;
	this->m_head = new Node<ElemType>;
	this->m_curPos = NULL;
}
template <class ElemType>
LinkList<ElemType>::~LinkList() {
	delete m_head;
	m_head = NULL;
	delete m_curPtr;
	m_curPtr = NULL;
}
template <class ElemType>
int LinkList<ElemType>::getLength() const {
	return m_length;
}
template <class ElemType>
bool LinkList<ElemType>::getElem(int pos, ElemType & elem) const {
	if (m_length == 0) {
#ifdef REMIND
		std::cout << "链表长度为0,无法查找pos位置上的值!\n";
#endif // REMIND
		return false;
	}
	if (pos < 1 || pos > m_length) {
		std::cout << "位置不合法!\n";
		return false;
	}
	
	Node<ElemType> * tempPtr = getElemPtr(pos);
	if (tempPtr) {							//其实不那个判断,因为得到NULL的结果已经被返回false了;
		elem = tempPtr->data;
		return true;
	}
	else {
#ifdef REMIND
		std::cout << "无法得到指定位置的指针所以无法得到其值" << endl;
#endif // REMIND
		return false;
	}
}
template <class ElemType>
Node<ElemType> * LinkList<ElemType>::getCurPtr() const {
	return m_curPtr;
}
template <class ElemType>
Node<ElemType> * LinkList<ElemType>::getElemPtr(int pos) const{
	if (pos < 0 || pos > m_length) {
#ifdef REMIND
		std::cout << "pos位置不合法!\n";
#endif // REMIND
		return NULL;
	}
	if (m_curPos == 0 && m_length == 0) {		//解决初始化时求0位置时的指针
		m_curPos = 0;
		m_curPtr = this->m_head;
	}
	if (m_curPos > pos) {
		m_curPos = 0;
		m_curPtr = this->m_head;
	}
	for (; m_curPos < pos; m_curPos++) {
		m_curPtr = m_curPtr->next;
	}

	return m_curPtr;
}
template <class ElemType>
bool LinkList<ElemType>::isEmpty() const {
	if (m_length == 0) {
		return true;
	}
	else {
		return false;
	}
}
template <class ElemType>
bool LinkList<ElemType>::insertElem(int pos, const ElemType & elem) {
	
	if (pos < 1 || pos > m_length + 1) {	//注意这里m_length+1,因为表示插在length+1也合理
		std::cout << "位置不合法!\n";
		return false;
	}
	Node<ElemType> * tempPtr = new Node<ElemType>(elem);
	Node<ElemType> * tempPtrTwo = getElemPtr(pos-1);
	tempPtr->next = tempPtrTwo->next;
	tempPtrTwo->next = tempPtr;
	m_length++;
	return true;
}
template <class ElemType>
void LinkList<ElemType>::insertBehindAll(const ElemType & elem) {
	insertElem(m_length + 1, elem);
}
template <class ElemType>
bool LinkList<ElemType>::setElem(int pos, const ElemType & elem) {
	Node<ElemType> * tempPtr = getElemPtr(pos);
	if (pos < 1) {
#ifdef REMIND
		std::cout << "pos位置不合法";		//其他pos不合法位置提示由getElemPtr给出
#endif // REMIND
		return false;
	}
	if (tempPtr) {
		tempPtr->data = elem;
		return true;
	}
	else {
		return false;
	}
}
template <class ElemType>
bool LinkList<ElemType>::deteleElem(int pos, ElemType & elem) {
	if (pos < 1) {
#ifdef REMIND
		std::cout << "pos位置不合法";		//其他pos不合法位置提示由getElemPtr给出
#endif // REMIND
		return false;
	}

	Node<ElemType> * tempPtr = getElemPtr(pos - 1);

	if (tempPtr) {
		Node<ElemType> * tempPtrTwo = tempPtr->next;
		tempPtr->next = tempPtrTwo->next;
		delete tempPtrTwo;
		tempPtrTwo = NULL;
		m_length--;
		return true;
	}
	else {
		return false;
	}
}
template <class ElemType>
void LinkList<ElemType>::display() const {
	std::cout << "链表的长度为:" << m_length << std::endl;
	std::cout << "链表头结点指针为:" << m_head << std::endl;
	std::cout << "链表的curPos为:" << m_curPos << std::endl;
	std::cout << "curPos指向的指针为:" << m_curPtr << std::endl;
	
	std::cout << "链表内的元素为:" << std::endl;
	ElemType elem;
	for (int i = 1; i <= m_length; i++) {
		getElem(i, elem);
		std::cout << elem << " ";
	}
	std::cout << endl;
}
#endif // !LINKLIST_H_INCLUDE
