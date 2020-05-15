/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/10/27
************************************************************************************/
/************************************************************************************
*Problem	:
*Tips:		:
			1.链式队列并没有设置长度,我估计是考虑到如果用到队列得话求长度操作应该不会经常
			用到,所以不必要设置length保护数据成员以免每次入队出队时增加操作。但是如果用到
			队列时并且多次需要求队长但是出对入队很少得话可以添加length保护数据成员，这是
			一个可以优化代码的地方
************************************************************************************/
/************************************************************************************
*History	:

************************************************************************************/
#ifndef LINKQUEUE_H_INCLUDE
#define LINKQUEUE_H_INCLUDE

#include "Node.h"
#include <iostream>

//#define REMIND
//#define DEBUG

template <class ElemType>
class LinkQueue {
	/***********************************公共接口声明*******************************/
public:
//基本成员函数
	LinkQueue();

	LinkQueue(const LinkQueue<ElemType> & copy);

	virtual ~LinkQueue();
//特征函数
	//得
	int getLength() const;

	bool getFrontElem(ElemType & elem) const;
	//判
	bool isEmpty() const;

	//插
	void inQueue(const ElemType & elem);

	//改
	//无

	//删
	bool outQueue(ElemType & elem);

	void clean();
//特殊函数
	
	void display() const;

//重载函数

	LinkQueue<ElemType> & operator=(const LinkQueue<ElemType> & copy);
/*=================================公共接口声明完毕============================*/
/***********************************保护接口声明*******************************/
private:
	Node<ElemType> * head, *rear;

/*=================================保护接口声明完毕============================*/
};

/***********************************公共接口实现*******************************/
template <class ElemType>
LinkQueue<ElemType>::LinkQueue() {
	head = rear = new Node<ElemType>;
}
//函数功能: 赋值构造函数
template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> & copy) {
	head = rear = new Node<ElemType>;

	for (Node<ElemType> * tempNode = copy.head->next; tempNode != NULL; tempNode = tempNode->next) {
		this->inQueue(tempNode->data);
	}
	
}
//函数功能: 析构函数
template <class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
	this->clean();
	delete head;

	//因为clean()后head 和 rear 指向的是同一块空间,所以释放head之后释放rear就访问出错
	//delete rear;							//错误的语句
}
//函数名称: int getLength() const;
//函数功能: 队列为空则返回长度0，否则遍历队列得长度返回
//注意事项: 因为每求一次长度便会遍历指针,所以如果需要多次用到长度得话会增加时间复杂度
template <class ElemType>
int LinkQueue<ElemType>::getLength() const {
	int length = 0;

	if (this->isEmpty()) {
		return length;
	}
	else {
		for (Node<ElemType> * tempNode = this->head->next; tempNode != NULL; tempNode = tempNode->next) {
			length++;
		}
		return length;
	}
}
//函数名称: bool getFrontElem(ElemType & elem) const
//函数功能: 队列为空返回假，否则取队头元素利用引用调用带回
//其子函数: bool isEmpty() const
template <class ElemType>
bool LinkQueue<ElemType>::getFrontElem(ElemType & elem) const {
	if (this->isEmpty()) {
		return false;
	}
	else {
		elem = head->next->data;
		return true;
	}
}
//函数名称: bool isEmpty() const
//函数功能: 若队头等于队尾返回真，否则返回假
template <class ElemType>
bool LinkQueue<ElemType>::isEmpty() const {
	if (head == rear) {
		return true;
	}
	else {
		return false;
	}
}
//函数名称: void inQueue(const ElemType & elem)
//函数功能：将elem入队，并不存在失败问题，因为链表不会满
template <class ElemType>
void LinkQueue<ElemType>::inQueue(const ElemType & elem) {
	Node<ElemType> * tempNode = new Node<ElemType>(elem);
	rear->next = tempNode;
	rear = tempNode;
}
//函数名称: bool outQueue(ElemType & elem) 
//函数功能: 队为空返回假，否则将队头出队由引用调用传出返回真，并且检测若出队后无元素
//			的话将rear == front；
//其子函数: bool isEmpty() const;
template <class ElemType>
bool LinkQueue<ElemType>::outQueue(ElemType & elem) {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "队列为空，不能出队！" << std::endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempNode;

		tempNode = head->next;
		elem = tempNode->data;
		head->next = tempNode->next;

		if (head->next == NULL) {			//此时rear指向的空间已被销毁
			rear = head;
		}

		delete tempNode;					//应该先将rear 指向 head后再释放rear和tempNode所指向的空间
		return true;
	}
}
//函数名称: void clean()
//函数功能：将队列清空
//其子函数: bool outQueue(ElemType & elem)
template <class ElemType>
void LinkQueue<ElemType>::clean() {
	ElemType tempElem;

	while (this->getLength() > 0) {
		this->outQueue(tempElem);
	}
}
//函数名称: void display() const
//函数功能: 输出队列相关信息
template <class ElemType>
void LinkQueue<ElemType>::display() const {
	if (this->isEmpty()) {
		std::cout << "队列为空" << std::endl;
	}
	else {
		std::cout << "队列长度为：" << this->getLength() << endl;
		std::cout << "队头至队尾元素分别为：" << endl;
		for (Node<ElemType> * tempNode = head->next; tempNode != NULL; tempNode = tempNode->next) {
			std::cout << tempNode->data << endl;
		}
	}
}
//函数名称: LinkQueue<ElemType> & operator=(const LinkQueue<ElemType> & copy)
//函数功能: 重载运算符=
//其子函数: void clean()
template <class ElemType>
LinkQueue<ElemType> & LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> & copy) {
	this->clean();

	for (Node<ElemType> * tempNode = copy.head->next; tempNode != NULL; tempNode = tempNode->next) {
		this->inQueue(tempNode->data);
	}

	return *this;
}
#endif // !LINKQUEUE_H_INCLUDE
