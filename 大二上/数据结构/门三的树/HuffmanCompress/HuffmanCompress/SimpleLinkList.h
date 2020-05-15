/************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/16
**************************************************************/
/***********************************************************
*Problem	:
*Tips:		:
			1.因为链表的得,增,删都得需要前一个位置或者这个一个位置
			的指针,所以在私有成员里面设置一个方法,用来简化代码
			2.在链表的代码理解上,注意链子在某个时刻指向哪里就好
			3.将插头和插尾建立在insert上,而insert建立在getElemPtr上
			,所以在插头的时候需要得到头指针,需要修改github上的源码,
			将pos = 0时返回头指针，而不检测是否为空,不知道自己修改的
			对不对。测试完后无任何问题。
*************************************************************/
/************************************************************
*History	:

*************************************************************/

#ifndef SIMPLELINKLIST_H_INCLUDE
#define SIMPLELINKLIST_H_INCLUDE

#include "Node.h"
#include <iostream>
//#define DEBUG								//打开调试信息
//#define REMIND
template <class ElemType>
class SimpleLinkList {
	/****************************公共接口*********************/
public:
//基本成员函数
	SimpleLinkList();

	SimpleLinkList(const SimpleLinkList<ElemType> & copy);

	virtual ~SimpleLinkList();
//特征成员函数
	//得
	int getLength() const;
	
	bool getElem(int pos, ElemType & elem) const;

	bool getElemPos(int & pos, const ElemType & elem) const;
	//判
	bool isEmpty() const;

	//插
	bool insert(int pos, const ElemType & elem);

	bool insertBeforeAll(const ElemType & elem);

	bool insertAfterAll(const ElemType & elem);

	//改

	bool setElem(int pos, const ElemType & elem);

	//删
	bool deleteElem(int pos, ElemType & elem);

	bool deleteElemByVal(const ElemType & elem);

	void clean();
	//重载函数
	SimpleLinkList & operator=(const SimpleLinkList<ElemType> & copy);
	//特殊处理函数
	//未定义
	
protected:
//保护函数成员
	Node<ElemType> * getElemPtr(int pos) const;

//保护数据成员
	Node<ElemType> * head;

	int length;
};

/*************************保护成员函数**************************/
//函数功能:得到参数pos位置的指针
//操作结果:得到参数pos位置的指针
//无子函数
template <class ElemType>
Node<ElemType> * SimpleLinkList<ElemType>::getElemPtr(int pos) const {
#ifdef DEBUG
	std::cout << "getElemPtr..." << std::endl;
#endif
	int curPos = 0;
	Node<ElemType> * tempPtr = head;
	//将下面代码注释掉的原因是想在pos = 0的时候返回头指针的地址以提供给insertBeforeAll()
	/*
	if (length = 0) {
#ifdef REMIND
		std::cout << "链表为空,无法得到元素指针" << endl;
#endif
		return NULL;
	}
	*/

	while (curPos < pos && tempPtr != NULL) {
		curPos++;
		tempPtr = tempPtr->next;
	}
	if (curPos == pos && tempPtr != NULL) {
		return tempPtr;
	}
	else return NULL;
}
/*======================保护成员函数实现完毕==============*/
/***********************基本成员函数实现*******************/
//函数名称:SimpleLinkList();
//函数功能:默认构造函数
//无子函数
template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList() {
	head = new Node<ElemType>;
	length = 0;
}
//函数名称:SimpleLinkList(const SimpleLinkList<ElemType> & copy)
//函数功能:赋值构造函数
//其子函数:getElem(),insertAfterAll();
template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> & copy) {
	head = new Node<ElemType>;
	length = 0;
	ElemType tempElem;
	
	for (int i = 1; i <= copy.getLength(); i++) {
		copy.getElem(i, tempElem);
		this->insertAfterAll(tempElem);
	}
}
template <class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList() {
	clean();
	delete head;
}
/*=====================基本成员函数实现完毕=================*/

/************************特征成员函数实现******************/
/*
int getLength() const;
bool getElem(int pos, ElemType & elem) const;
bool getElemPos(int & pos, const ElemType & elem) const;
bool isEmpty() const;
bool insert(int pos, const ElemType & elem);
bool insertBeforeAll(const ElemType & elem);
bool insertAfterAll(const ElemType & elem);
bool setElem(int pos, const ElemType & elem);
bool deleteElem(int pos, ElemType & elem);
bool deleteByVal(const ElemType & elem);
void clean();
*/
//函数名称:int getLength() const
//函数功能:得到链表长度
//操作结果:返回链表结果
template <class ElemType>
int SimpleLinkList<ElemType>::getLength() const {
	return length;
}
//函数名称:bool getElem(int pos, ElemType & elem) const
//函数功能:链表为空或pos < 1 || pos > length返回假,否则利用形参得到pos位置上元素的值并返回真
template <class ElemType>
bool SimpleLinkList<ElemType>::getElem(int pos, ElemType & elem) const {
	if (length == 0) {
#ifdef REMIND
		std::cout << "链表为空,无法查询元素" << std::endl;
#endif
		return false;
	}
	if (pos < 1 || pos > length) {			
#ifdef REMIND
		std::cout << "位置非法" << std::endl;
#endif
		return false;
	}
	else {	
		Node<ElemType> * tempPtr;

		tempPtr = this->getElemPtr(pos);
		elem = tempPtr->data;
		return true;	
	}
}
//函数名称:bool getElemPos(int & pos, const ElemType & elem)
//函数功能:无此元素返回假并且pos=-1,有此元素返回真并且得到的位置由pos返回
template <class ElemType>
bool SimpleLinkList<ElemType>::getElemPos(int & pos, const ElemType & elem) const {
#ifdef DEBUG
	std::cout << "getElemPos..." << std::endl;
#endif
	pos = -1;
	Node<ElemType> * tempPtr;
	ElemType tempElem;

	tempPtr = head;
	for (int i = 1; i <= length; i++) {
		this->getElem(i, tempElem);
		if (tempElem == elem) {
			pos = i;
			return true;
		}
	}
	return false;
}
//函数名称:bool SimpleLinkList<ElemType>::isEmpty() const
//函数功能:如果链表为空则返回真,否则返回假
template <class ElemType>
bool SimpleLinkList<ElemType>::isEmpty() const {
#ifdef DEBUG
	std::cout << "isEmpty..." << std::endl;
#endif
	return length == 0;
}
//函数名称:bool insert(int pos, const ElemType & elem)
//函数功能:插入成功返回1,否则返回0
template <class ElemType>
bool SimpleLinkList<ElemType>::insert(int pos, const ElemType & elem) {

	if (pos < 1 || pos > length + 1) {
#ifdef REMIND
		std::cout << "位置不合法" << std::endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempPtr;
		Node<ElemType> * targetPtr;

		tempPtr = this->getElemPtr(pos - 1);
		targetPtr = new Node<ElemType>(elem, tempPtr->next);
		tempPtr->next = targetPtr;
		length++;
		return true;		
	}
}
//函数名称:bool insertBeforeAll(const ElemType & elem)
//函数功能:插入成功返回1
template <class ElemType>
bool SimpleLinkList<ElemType>::insertBeforeAll(const ElemType & elem) {
#ifdef DEBUG
	std::cout << "insertBeforeAll..." << std::endl;
#endif
	this->insert(1, elem);
	return true;
}
//函数名称:bool insertAfterAll(const ElemType & elem)
//函数功能:插入链表尾部,成功返回1,否则返回0
template <class ElemType>
bool SimpleLinkList<ElemType>::insertAfterAll(const ElemType & elem) {
#ifdef DEBUG
	std::cout << "insertAfterAll..." << std::endl;
#endif
	this->insert(length + 1, elem);
	return true;
}
//函数功能:bool setElem(int pos, const ElemType & elem)
//函数功能:重置某位置元素的值,成功返回1,位置不合法返回0
template <class ElemType>
bool SimpleLinkList<ElemType>::setElem(int pos, const ElemType & elem) {
#ifdef DEBUG
	std::cout << "setElem..." << std::endl;
#endif
	if (pos < 1 || pos > length) {
#ifdef REMIND
		std::cout << "位置不合法" << std::endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempPtr;

		tempPtr = this->getElemPtr(pos);
		tempPtr->data = elem;
		return true;
	}
}
//函数名称:bool deleteElem(int pos, ElemType & elem)
//函数功能:删除某个位置元素的值,成功返回1,如果pos < 1 || pos > length返回0并且返回elem为-1;
template <class ElemType>
bool SimpleLinkList<ElemType>::deleteElem(int pos, ElemType & elem) {
#ifdef DEBUG
	std::cout << "deleteElem..." << std::endl;
#endif
	if (pos < 1 || pos > length) {
#ifdef REMIND
		std::cout << "位置不合法" << std::endl;
#endif
		elem = -1;
		return false;
	}
	else {
		Node<ElemType> * tempPtr;
		Node<ElemType> * targetPtr;

		tempPtr = this->getElemPtr(pos - 1);
		targetPtr = tempPtr->next;
		elem = targetPtr->data;
		tempPtr->next = targetPtr->next;
		delete targetPtr;					//注意释放空间
		length--;
		return true;
	}
}
//函数名称:bool deleteElemByVal(const ElemType & elem)
//函数功能:删除链表中全部某个值的元素,必定成功返回1
template <class ElemType>
bool SimpleLinkList<ElemType>::deleteElemByVal(const ElemType & elem) {
#ifdef DEBUG
	std::cout << "deleteElemByVal..." << std::endl;
#endif
	int tempPos;
	ElemType tempElem;

	this->getElemPos(tempPos, elem);
	while (tempPos) {
		this->deleteElem(tempPos, tempElem);
		this->getElemPos(tempPos, elem);
		return true;
	}
	return true;
}
//函数名称:void clean()
//函数功能:清空链表
template <class ElemType>
void SimpleLinkList<ElemType>::clean() {
#ifdef DEBUG
	std::cout << "clean..." << std::endl;
#endif
	ElemType tempElem;
	while (length) {
		this->deleteElem(1, tempElem);
	}
}
/*====================特征成员函数实现完毕==================*/
/*********************重载函数实现***********************/
//函数名称:=
//函数功能:重载运算符
template <class ElemType>
SimpleLinkList<ElemType> & SimpleLinkList<ElemType>:: operator=(const SimpleLinkList<ElemType> & copy) {
	ElemType tempElem;

	if (this->length != 0) {
		this->clean();
	}

	for (int i = 1; i <= copy.getLength(); i++) {
		copy.getElem(i, tempElem);
		this->insertAfterAll(tempElem);
	}

	return *this;
	
}
/*==================重载函数实现完毕=====================*/
#endif