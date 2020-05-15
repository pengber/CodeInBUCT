/************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/18
**************************************************************/
/***********************************************************
*Problem	:
			1.有一个矛盾出现了,那刚开始初始化循环链表时,会有一个头结点
			,所以length = 1,但是此时数据域的值是垃圾值,所以当链表刚初
			始化如果调用insert(length+1,elem)时就会出错
			
*Tips:		:
			1.循环链表和单向链表的不同之处有下面几点
			1)构造的时候将头结点->next指向本身而不是NULL
			2)如果插入的是链表尾部的话需要在构造Node的时候将->next指向head即可

			2.我认为,如果有头结点的循环链表失去了它本身循环的意义,
			会在处理数据循环的时候考虑那个没有存储数据的空的头结点
			所以循环链表的最好的姿势是用不带头结点的链表,然后循环

			
*************************************************************/
/************************************************************
*History	:
2019/11/18日：
			对部分代码进行了更新（解决了问题1）：
			0.构造函数，默认构造函数循环链表的长度为0，头指针为空，而不是之前定义的长度为1，头指针指向自己
			1.插入代码，插入位置为1时，构建循环链表头指针并将首元素置为对应值
			2.删除代码，先判断长度是否为1，长度为1时，直接删除头指针，否则照对应pos删除
			循环链表的理解：
			循环链表初始化应该为NULL，并且应该为不带头节点的链表，这样在初始化时就不用申请空间，而是在插入或者删除时需要判别，如果长度为1时，应该对头节点做特殊处理，其他的话正常就好。
*************************************************************/
#ifndef CIRCLELINKLIST_H_INCLUDE
#define CIRCLELINKLIST_H_INCLUDE
#include <iostream>
#include "Node.h"
#include "PolyItem.h"
//#define DEBUG
//#define REMIND
template <class ElemType>
class CircleLinkList {
	/************************公共接口声明***************************/
public:
//基本成员函数
	CircleLinkList();

	CircleLinkList(const CircleLinkList & copy);

	virtual ~CircleLinkList();
//特征成员函数
	//得
	int getLength() const;

	bool getElem(int pos, ElemType & elem) const;

	//判
	bool isEmpty() const;

	//增
	bool insert(int pos, const ElemType & elem);

	//改
	bool setElem(int pos, const ElemType & elem);

	//删
	bool deleteElem(int pos, ElemType & elem);


	void clean();
//重载函数

	//CircleLinkList & CirCleLinkList<ElemType>::operator=(const CircleLinkList & copy);
//特殊函数

	void ysfCircle();

	bool deletePtr(Node<ElemType> * current);

	double returnCoef(Node<ElemType> * current);

	/***********************公共接口声明完毕*************************/
	/************************保护接口声明************************/
protected:

	Node<ElemType> * getElemPtr(int pos) const;

	void init();

	Node<ElemType> * head;

	int length;
	/**********************保护接口声明完毕*********************/
};
/************************保护成员函数实现***************************/
template <class ElemType>
Node<ElemType> * CircleLinkList<ElemType>::getElemPtr(int pos) const {
#ifdef DEBUG
	std::cout << "getElemPtr..." << std::endl;
#endif
	if (pos < 1 || pos > length) {
#ifdef REMIND
		std::cout << "位置不合法,返回NULL指针" << std::endl;
#endif
		return NULL;
	}

	Node<ElemType> * tempPtr = head;
	if (pos == 1) {
		return tempPtr;
	}
	else {
		for (int tempPos = 2; tempPos <= pos; tempPos++) {
			tempPtr = tempPtr->next;
		}
		return tempPtr;
	}
}
/*===========================保护函数实现完毕======================*/

/************************基本成员函数实现*************************/
template <class ElemType>
CircleLinkList<ElemType>::CircleLinkList() {
	head = NULL;
	length = 0;
}
/*因为BUG不能调用insert(length+1,elem),所以先不定义
template <class ElemType>
CircleLinkList::CircleLinkList(const CircleLinkList<ElemType> & copy) {

}
*/
template <class ElemType>
CircleLinkList<ElemType>::~CircleLinkList() {
	this->clean();
	delete head;
}
/*=======================基本成员函数实现完毕======================*/
/************************特征函数实现*************************/
//函数名称:int getLength() const;
//函数功能:得到循环链表长度
//无子函数
template <class ElemType>
int CircleLinkList<ElemType>::getLength() const {
	return length;
}
//函数功能:bool getElem(int pos, ElemType & elem);
//函数功能:得到第pos个位置的元素的值
//其子函数:Node<ElemType> * getElemPtr();
template <class ElemType>
bool CircleLinkList<ElemType>::getElem(int pos, ElemType & elem) const {
#ifdef DEBUG
	std::cout << "getElem..." << std::endl;
#endif
	if (pos < 1 || pos > length) {
#ifdef REMIND
		std::cout << "输入位置有误,位置返回-1" << endl;
#endif
		pos = -1;
		return false;
	}
	else {
		Node<ElemType> * tempPtr;
		tempPtr = this->getElemPtr(pos);
		elem = tempPtr->data;
		return true;
	}
}
//函数名称:bool isEmpty() const;
//函数功能:判断链表是否为空,为空返回真,否则返回假
//其子函数:无子函数
template <class ElemType>
bool CircleLinkList<ElemType>::isEmpty() const {
	return head->next == head;
}
//函数功能:bool insert(int pos, const ElemType & elem)
//函数名称:在pos个位置上插入所插元素,pos < 1 || pos > length+1返回假,否则返回真
//其子函数:Node<ElemType> * getElemPtr();
template <class ElemType>
bool CircleLinkList<ElemType>::insert(int pos, const ElemType & elem) {
#ifdef DEBUG
	std::cout << "insert..." << std::endl;
#endif

	if (pos < 1 || pos > length + 1) {
#ifdef REMIND
		std::cout << "输入位置有误" << std::endl;
#endif
		return false;
	}
	else {
		if (pos == 1) {
			head = new Node<ElemType>(elem);
			head->next = head;
			length++;
			return true;
		}
		Node<ElemType> * tempPtr = this->getElemPtr(pos-1);
		Node<ElemType>  *newNode = new Node<ElemType>(elem, tempPtr->next);
		tempPtr->next = newNode;
		length++;
		return true;
	}
}
//函数名称:bool deleteElem(int pos, ElemType & elem)
//函数功能:删除pos位置上的元素,pos < 1 || pos > length返回假,否则返回真
//其子函数:Node<ElemType> * getElemPtr(int pos)
template <class ElemType>
bool CircleLinkList<ElemType>::deleteElem(int pos, ElemType & elem) {
#ifdef DEBUG
	std::cout << "deleteElem..." << std::endl;
#endif
	if (pos < 1 || pos > length) {
#ifdef REMIND
		std::cout << "位置不合法" << std::endl;
#endif
		return false;
	}
	Node<ElemType> * tempPtr;
	Node<ElemType> * deletePtr;
	if (length == 1) {
		elem = head->data;
		delete head;
		length--;
		return true;
	}
	if (pos == 1) {
		elem = head->data;
		deletePtr = head;
		tempPtr = this->getElemPtr(length);
		head = head->next;
		tempPtr->next = head;				//把头结点解了下来
		length--;
		return true;
	}
	else {
		tempPtr = this->getElemPtr(pos - 1);
		deletePtr = tempPtr->next;
		elem = deletePtr->data;
		tempPtr->next = deletePtr->next;
		length--;
		return true;
	}
}
//函数名称:
template <class ElemType>
bool CircleLinkList<ElemType>::deletePtr(Node<ElemType> * current) {
	Node<ElemType> * beforeCurrent = NULL;
	beforeCurrent = current;
	for (int i = 1; i <= length - 1; i++) {
		beforeCurrent = beforeCurrent->next;
	}
	beforeCurrent->next = current->next;
	length--;
	return true;
}
//函数名称:bool setElem(int pos, const ElemType & elem) 
//函数功能:置某个位置上的元素为elem
//其子函数:Node<ElemType> * getElemType(int pos);
template <class ElemType>
bool CircleLinkList<ElemType>::setElem(int pos, const ElemType & elem) {
#ifdef DEBUG
	std::cout << "setElem..." << std::endl;
#endif
	if (pos < 1 || pos > length) {
#ifdef REMING
		std::cout << "位置不合法" << endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempPtr = this->getElemPtr(pos);
		tempPtr->data = elem;
		return true;
	}
}

template <class ElemType>
void CircleLinkList<ElemType>::clean() {
	ElemType  tempElem;

	while (head->next != head) {
		this->deleteElem(1, tempElem);
	}
}
//函数名称:
//函数功能:
template <class ElemType>
void CircleLinkList<ElemType>::ysfCircle() {
	int n, i = 1;
	PolyItem tempItem;
	Node<ElemType>  * tempNode = head;
	this->getElem(1, tempItem);
	n = tempItem.mExpn;

	while (this->getLength() != 0) {
		if (i == n) {
			std::cout << this->returnCoef(tempNode) << "OUT" << std::endl;
			this->deletePtr(tempNode);
			i = 0;
			n = tempItem.mExpn;
		}
		i++;
		tempNode = tempNode->next;
	}
}

template <class ElemType>
double CircleLinkList<ElemType>::returnCoef(Node<ElemType> * current) {
	Node<ElemType> * tempPtr = head;
	
	for (int i = 1; i <= this->getLength() + 100; i++) {//我也不知道为什么加100,但就是能成功
		if (tempPtr == current)
			return current->data.mCoef;
		tempPtr = tempPtr->next;
	}

	return 0;
}
/*============================特征函数实现完毕===========================*/
#endif