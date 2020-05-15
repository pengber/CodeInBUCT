using namespace std;
#include <stdexcept>
#include <exception>
#include <iostream>
#include "assert.h"							//检测申请新空间是否成功需要
#include <typeinfo>							//输出root类型需要
//#define DEBUG								//打开显示函数信息
//#define REMIND							//打开显示提示信息
//#define SHOW								//打开显示空结点


#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE
#include <iostream>
template <class ElemType>
struct Node {
public:
	Node();
	Node(const ElemType & elem, Node<ElemType> * link = NULL);
	virtual ~Node();
	ElemType data;
	Node<ElemType> * next;
};
//函数名称:Node()
//函数功能:默认构造函数
//操作结果:返回一个指针域指向NULL的结点
template <class ElemType>
Node<ElemType>::Node() {
	this->next = NULL;
}
//函数名称:Node(const ElemType & elem, Node<ElemType> * link)
//函数功能:赋值构造函数
//操作结果:创建一个由数据信息的结点
template <class ElemType>
Node<ElemType>::Node(const ElemType & elem, Node<ElemType> * link) {
	this->data = elem;
	this->next = link;
}
//函数名称:virtual ~Node()
//函数功能:析构函数
template <class ElemType>
Node<ElemType>::~Node() {

}
#endif // !NODE_H_INCLUDE


#ifndef LINKQUEUE_H_INCLUDE
#define LINKQUEUE_H_INCLUDE

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

#ifndef BINTREENODE_H_INCLUDE
#define BINTREENODE_H_INCLUDE

template <class ElemType>
struct BinTreeNode {
	ElemType data;
	BinTreeNode<ElemType> * leftChild;
	BinTreeNode<ElemType> * rightChild;

	BinTreeNode();
	BinTreeNode(const ElemType & data, BinTreeNode<ElemType> * leftChild = NULL,
		BinTreeNode<ElemType> * rightChild = NULL);
	virtual ~BinTreeNode();
};

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode() {
	leftChild = rightChild = NULL;
}

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType & data, BinTreeNode<ElemType> * leftChild,
	BinTreeNode<ElemType> * rightChild) {

	this->data = data;
	this->leftChild = leftChild;
	this->rightChild = rightChild;
}

template <class ElemType>
BinTreeNode<ElemType>::~BinTreeNode() {
	delete leftChild;
	delete rightChild;
}
#endif

template <class ElemType>
class BinaryTree {
	/************************************公共接口**********************************/
public:
	//基本成员函数
	BinaryTree();
	BinaryTree(const ElemType & elem);		//以elem为root建立树
	BinaryTree(const BinTreeNode<ElemType> * &root);				//以root指针为根节点建立树
	BinaryTree(const BinaryTree<ElemType> * &copy);				//复制构造函数
	virtual ~BinaryTree();
	//特征函数
	//得：节点数，深度，根节点，双亲，左右孩子,指针元素值
	int getNodeCount() const;

	int getHeight() const;

	BinTreeNode<ElemType> * getRoot() const;

	BinTreeNode<ElemType> * getParent(const BinTreeNode<ElemType> * &cur) const;

	BinTreeNode<ElemType> * getLeftChild(const BinTreeNode<ElemType> * &cur) const;

	BinTreeNode<ElemType> * getRightChild(const BinTreeNode<ElemType> * &cur) const;

	ElemType getElem(BinTreeNode<ElemType> * &cur) const;
	//判：空
	bool isEmpty() const;

	//增
	void insertLeftChild(BinTreeNode<ElemType> * &cur, const ElemType & elem);

	void insertRightChild(BinTreeNode<ElemType> * &cur, const ElemType & elem);

	void preCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &));//已知前序遍历序和空结点信息

	void inCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &));//已知中序遍历序和空结点

	void postCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &));//已知前序遍历序和空结点信息

	bool createByPreInOrder(ElemType * preOrder, ElemType * inOrder, int length, ElemType & nullElem);


	//改
	bool setElem(BinTreeNode<ElemType> * &cur, const ElemType & elem);

	//删
	void deleteLeftChildNode(BinTreeNode<ElemType> * &cur);

	void deleteRightChildNode(BinTreeNode<ElemType> * &cur);

	void deleteLeftChildTree(BinTreeNode<ElemType> * &cur);

	void deleteRightChildTree(BinTreeNode<ElemType> * &cur);

	void destroy();
	//遍历
	void preOrder(void(*visit)(ElemType &));

	void inOrder(void(*visit)(ElemType &));

	void postOrder(void(*visit)(ElemType &));

	void levelOrder(void(*visit)(ElemType &));

	/*===============================公共接口声明完毕==============================*/
	/************************************保护接口**********************************/
protected:
	BinTreeNode<ElemType> * root;

	//辅助函数
	BinTreeNode<ElemType> * copyTreeHelp(BinTreeNode<ElemType> * &copy) const;

	//得：节点数，深度
	int getNodeCountHelp(BinTreeNode<ElemType> * &root) const;

	int getHeightHelp(BinTreeNode<ElemType> * &root) const;

	BinTreeNode<ElemType> * getParentHelp(const BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const;

	//判无辅助函数
	//增
	void preCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));

	void inCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));

	void postCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));

	void createByPreInOrderHelp(BinTreeNode<ElemType> * &root, ElemType * preOrder, ElemType * inOrder, int length, ElemType & nullelem);

	//改无辅助函数
	//删
	void deleteNodeHelp(BinTreeNode<ElemType> * &cur);

	void destroyHelp(BinTreeNode<ElemType> * &root);

	//遍历辅助函数
	void preOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;

	void inOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;

	void postOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;

	void levelOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;
	//非递归遍历辅助函数
	void nonRecurPreOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &));

	void nonRecurInOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &));
	/*===============================保护接口声明完毕==============================*/
};
/*******************************保护成员函数实现*********************************/
/*
BinTreeNode<ElemType> * copyTreeHelp(BinTreeNode<ElemType> * &copy);
int getNodeCountHelp(const BinTreeNode<ElemType> * &root) const;
int getHeightHelp(const BinTreeNode<ElemType> * &root) const;
BinTreeNode<ElemType> * getParentHelp(const BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const;
void preCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
void inCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
void postCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
void destroyHelp(BinTreeNode<ElemType> * &root);
void preOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;
void inOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;
void postOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const;
*/
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::copyTreeHelp(BinTreeNode<ElemType> * &copy) const {
#ifdef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << _line_ << std::endl;
#endif // DEBUG

	if (copy == NULL) {
		return NULL;
	}
	else {
		BinTreeNode<ElemType> * leftChild = copyTreeHelp(copy->leftChild);
		BinTreeNode<ElemType> * rightChild = copyTreeHelp(copy->rightChild);
		BinTreeNode<ElemType> * newBinTreeNode = new BinaryTree(copy->data, leftChild, rightChild);

		return newBinTreeNode;
	}
}
template <class ElemType>
int BinaryTree<ElemType>::getNodeCountHelp(BinTreeNode<ElemType> * &root) const {
#ifdef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (root == NULL) {
		return 0;
	}
	else {
		int leftCount = getNodeCountHelp(root->leftChild);
		int rightCount = getNodeCountHelp(root->rightChild);
		return 1 + leftCount + rightCount;
	}
}
template <class ElemType>
int BinaryTree<ElemType>::getHeightHelp(BinTreeNode<ElemType> * &root) const {
#ifdef REMIND
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // REMIND
	if (root == NULL) {
		return 0;
	}
	else {
		int leftHeight = getHeightHelp(root->leftChild);
		int rightHeight = getHeightHelp(root->rightChild);
		return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
	}
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getParentHelp(const BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const {
#ifdef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << endl;
#endif // DEBUG
	if (root == NULL) {
		//// std::invalid_argument("空结点无双亲结点！") << std::endl;
	}
	else if (root->leftChild == cur || root->rightChild == cur) {
		return root;
	}
	else {
		BinTreeNode<ElemType>  * tempNode = NULL;
		if (tempNode = getParentHelp(root->leftChild)) return tempNode;
		if (tempNode = getParentHelp(root->rightChild)) return tempNode;
	}
}
template <class ElemType>
void BinaryTree<ElemType>::preCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUN:" << __FUNCTION__ << ",LINE:" << __LINE__ << endl;
#endif // DEBUG
	ElemType elem;
	(*visit)(elem);

	if ((*isNull)(elem)) {
		root = NULL;
	}
	else {
		root = new BinTreeNode<ElemType>(elem);
		assert(root);
		preCreateHelp(root->leftChild, visit, isNull);
		preCreateHelp(root->rightChild, visit, isNull);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::inCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << endl;
#endif // DEBUG
	ElemType elem;
	(*visit)(elem);

	if ((*isNull)(elem)) {
		root = NULL;
	}
	else {
		inCreateHelp(root->leftChild, visit, isNull);
		root = new BinTreeNode<ElemType>(elem);
		assert(root);
		inCreateHelp(root->rightChild, visit, isNull);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::postCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << endl;
#endif // DEBUG
	ElemType elem;
	(*visit)(elem);

	if ((*isNull)(elem)) {
		root = NULL;
	}
	else {
		postCreateHelp(root->leftChild, visit, isNull);
		postCreateHelp(root->rightChild, visit, isNull);
		root = new BinTreeNode<ElemType>(elem);
		assert(root);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::createByPreInOrderHelp(BinTreeNode<ElemType> * &root, ElemType * preOrder, ElemType * inOrder, int length, ElemType & nullElem) {
	if (length == 0) {
		root = NULL;//root = new BinTreeNode<ElemType>(nullElem);
		return;
	}
	else {
		root = new BinTreeNode<ElemType>(preOrder[0]);
	}
	int rootLocation = 0;
	int leftTreeLength = 0;
	int rightTreeLength = 0;

	for (int i = 0; i < length; i++) {
		if (root->data == inOrder[i]) {
			rootLocation = i;
			leftTreeLength = i - 0;
			rightTreeLength = length - i - 1;
			break;
		}
	}
	ElemType * leftTreePreOrder = preOrder + 1;
	ElemType * leftTreeInOrder = inOrder;

	ElemType * rightTreePreOrder = leftTreePreOrder + leftTreeLength;
	ElemType * rightTreeInOrder = inOrder + rootLocation + 1;
	createByPreInOrderHelp(root->leftChild, leftTreePreOrder, leftTreeInOrder, leftTreeLength, nullElem);
	createByPreInOrderHelp(root->rightChild, rightTreePreOrder, rightTreeInOrder, rightTreeLength, nullElem);
}
template <class ElemType>
void BinaryTree<ElemType>::deleteNodeHelp(BinTreeNode<ElemType> * & cur) {
#ifdef DEBUG
	std::cout << "FUN:" << _func_ << "，LINE:" << _LINE_ << endl;
#endif // DEBUG

}
template <class ElemType>
void BinaryTree<ElemType>::destroyHelp(BinTreeNode<ElemType> * &root) {
	if (root == NULL) {
		return;
	}
	else {
		destroyHelp(root->leftChild);
		destroyHelp(root->rightChild);
		delete root;
		root = NULL;
	}
}
template <class ElemType>
void BinaryTree<ElemType>::preOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const {
	if (root == NULL) {
#ifdef SHOW
		std::cout << "#";
#endif // SHOW
		return;
	}
	else {
		(*visit)(root->data);
		preOrderHelp(root->leftChild, visit);
		preOrderHelp(root->rightChild, visit);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::inOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const {
	if (root == NULL) {
#ifdef SHOW
		std::cout << "#";
#endif // SHOW
		return;
	}
	else {
		inOrderHelp(root->leftChild, visit);
		(*visit)(root->data);
		inOrderHelp(root->rightChild, visit);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::postOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const {
	if (root == NULL) {
#ifdef SHOW
		std::cout << "#";
#endif // SHOW
		return;
	}
	else {
		postOrderHelp(root->leftChild, visit);
		postOrderHelp(root->rightChild, visit);
		(*visit)(root->data);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::levelOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) const {
	LinkQueue<BinTreeNode<ElemType> * > queue;
	queue.inQueue(root);
	BinTreeNode<ElemType> * tempNode;

	while (!queue.isEmpty()) {
		queue.outQueue(tempNode);
		(*visit)(tempNode->data);
		if (tempNode->leftChild != NULL) queue.inQueue(tempNode->leftChild);
		if (tempNode->rightChild != NULL) queue.inQueue(tempNode->rightChild);
	}
}

/*=============================保护成员函数实现完毕=============================*/
/*******************************基本成员函数实现*********************************/
/*
*	BinaryTree();
BinaryTree(const ElemType & elem);		//以elem为root建立树
BinaryTree(const BinTreeNode<ElemType> * root);				//以root指针为根节点建立树
BinaryTree(const BinaryTree<ElemType> * copy);				//复制构造函数
*/

template <class ElemType>
BinaryTree<ElemType>::BinaryTree() {
	root = new BinTreeNode<ElemType>();
}
template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType & elem) {
	root = new BinTreeNode<ElemType>(elem);
}
template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinTreeNode<ElemType> * & root) {
	this->root = root;
}
template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> * &copy) {
	this->root = copy->getRoot();
}
template <class ElemType>
BinaryTree<ElemType>::~BinaryTree() {
	destroyHelp(root);
}
/*==============================基本成员函数实现完毕=============================*/
/**********************************特征函数实现*********************************/
/*
*得：节点数，深度，根节点，双亲，左右孩子,指针元素值
int getNodeCount() const;
int getHeight() const;
BinTreeNode<ElemType> * getRoot() const;
BinTreeNode<ElemType> * getParent(const BinTreeNode<ElemType> * &cur) const;
BinTreeNode<ElemType> * getLeftChild(const BinTreeNode<ElemType> * &cur) const;
BinTreeNode<ElemType> * getRightChild(const BinTreeNode<ElemType> * &cur) const;
ElemType getElem(const BinTreeNode<ElemType> * &cur) const;
bool isEmpty() const;
void insertLeftChild(BinTreeNode<ElemType> * &cur,const ElemType & elem);
void insertRightChild(BinTreeNode<ElemType> * &cur,const ElemType & elem);
void preCreate(BinTreeNode<ElemType> * &cur, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
void inCreate(BinTreeNode<ElemType> & cur, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
void postCreate(BinTreeNode<ElemType> * &cur, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
bool setElem(BinTreeNode<ElemType> * &cur, const ElemType & elem);
void deleteLeftChildNode(BinTreeNode<ElemType> * &cur);
void deleteRightChildNode(BinTreeNode<ElemType> * &cur);
void deleteLeftChildTree(BinTreeNode<ElemType> * &cur);
void deleteRightChildTree(BinTreeNode<ElemType> * &cur);
void preOrder(void(*visit)(ElemType &));
void inOrder(void(*visit)(ElemType &));
void postOrder(void(*visit)(ElemType &));
*/
template <class ElemType>
int BinaryTree<ElemType>::getNodeCount() const {
	BinTreeNode<ElemType> * tempNode = root;
	return getNodeCountHelp(tempNode);
}
template <class ElemType>
int BinaryTree<ElemType>::getHeight() const {
	/*----------------------------------------*/
	//去掉两个函数后面的const后,没有出错
	//return this->getHeightHelp(root);
	/*========================================*/

	/*----------------------------------------*/
	//此代码会显示错误
	//return getHeightHelp(root);
	/*========================================*/

	/*----------------------------------------*/
	//此代码不会显示错误(有const修饰)
	//BinTreeNode<ElemType> * tempNode = root;
	//return getHeightHelp(tempNode);
	/*========================================*/

	/*----------------------------------------*/
	//以下代码测试root类型
	//结果为:rootstruct BinTreeNode<char> *
	//cout << "root" << typeid(root).name() << endl;
	/*=========================================*/

	/*------------------------------------------*/
	//以下代码会显示错误
	//int height = getHeightHelp(root);
	//return height;
	/*========================================*/

	//最终采用const修饰,但使用一个间接变量,以保证"得"函数的const属性
	BinTreeNode<ElemType> * tempNode = root;
	return getHeightHelp(tempNode);
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getRoot() const {
	return root;
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getParent(const BinTreeNode<ElemType> * &cur) const {
	return getParentHelp(root, cur);
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getLeftChild(const BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		// std::invalid_argument("此结点为空，无左孩子!") << endl;
	}
	else {
		return cur->leftChild;
	}
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getRightChild(const BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		// std::invalid_argument("此结点为空，无左孩子!") << endl;
	}
	else {
		return cur->rightChild;
	}
}
template <class ElemType>
ElemType BinaryTree<ElemType>::getElem(BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		// std::invalid_argument("结点为空，没有值！\n");
	}
	else {
		return cur->data;
	}
}
template <class ElemType>
bool BinaryTree<ElemType>::isEmpty() const {
	return root == NULL;
}
template <class ElemType>
void BinaryTree<ElemType>::insertLeftChild(BinTreeNode<ElemType> * &cur, const ElemType & elem) {
	if (cur == NULL) {
		// std::invalid_argument("结点为空，不能插入左孩子！\n");
	}
	else {
		BinTreeNode<ElemType> * newNode = new BinTreeNode<ElemType>(elem);

		if (cur->leftChild != NULL) {
			newNode->leftChild = cur->leftChild;
		}
		cur->leftChild = newNode;
	}
}
template <class ElemType>
void BinaryTree<ElemType>::insertRightChild(BinTreeNode<ElemType> * &cur, const ElemType & elem) {
	if (cur == NULL) {
		// std::invalid_argument("结点为空，不能插入右孩子!\n");
	}
	else {
		BinTreeNode<ElemType> * newNode = new BinTreeNode<ElemType>(elem);

		if (cur->rightChild != NULL) {
			newNode->rightChild = cur->rightChild;
		}
		cur->rightChild = newNode;
	}
}
template <class ElemType>
void BinaryTree<ElemType>::preCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
	preCreateHelp(root, visit, isNull);
}
template <class ElemType>
void BinaryTree<ElemType>::inCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
	inCreateHelp(root, visit, isNull);
}
template <class ElemType>
void BinaryTree<ElemType>::postCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
	postCreateHelp(root, visit, isNull);
}
template <class ElemType>
bool BinaryTree<ElemType>::createByPreInOrder(ElemType * preOrder, ElemType * inOrder, int length, ElemType & nullElem) {
	createByPreInOrderHelp(root, preOrder, inOrder, length, nullElem);
	return true;
}
template <class ElemType>
bool BinaryTree<ElemType>::setElem(BinTreeNode<ElemType> * &cur, const ElemType & elem) {
	if (cur == NULL) {
		std::cout << "结点为空,无法设置值" << std::endl;
		return false;
	}
	else {
		cur->data = elem;
		return true;
	}
}
template <class ElemType>
void BinaryTree<ElemType>::deleteLeftChildNode(BinTreeNode<ElemType> * &cur) {
	deleteNodeHelp(cur->leftChild);
}
template <class ElemType>
void BinaryTree<ElemType>::deleteRightChildNode(BinTreeNode<ElemType> * &cur) {
	deleteNodeHelp(cur->rightChild);
}
template <class ElemType>
void BinaryTree<ElemType>::deleteLeftChildTree(BinTreeNode<ElemType> * &cur) {
	if (cur == NULL) {
		// std::invalid_argument("结点为空，不能删除左子树！\n");
	}
	else {
		destroyHelp(cur->leftChild);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::deleteRightChildTree(BinTreeNode<ElemType> * &cur) {
	if (cur == NULL) {
		// std::invalid_argument("结点为空，不能删除右子树！\n");
	}
	else {
		destroyHelp(cur->rightChild);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::destroy() {
	if (root == NULL);
	else {
		destroyHelp(this->root);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::preOrder(void(*visit)(ElemType &)) {
	preOrderHelp(this->root, visit);
}
template <class ElemType>
//函数名称: void inOrder(void(*visit)(ElemType &))
//函数功能: 输出中序遍历,不含虚结点
void BinaryTree<ElemType>::inOrder(void(*visit)(ElemType &)) {
	inOrderHelp(this->root, visit);
}
template <class ElemType>
void BinaryTree<ElemType>::postOrder(void(*visit)(ElemType &)) {
	postOrderHelp(this->root, visit);
}
template <class ElemType>
void BinaryTree<ElemType>::levelOrder(void(*visit)(ElemType &)) {
	levelOrderHelp(this->root, visit);
}
/*================================特征函数实现完毕=============================*/




using namespace std;
void read(char &);
void write(char &);
bool isNull(char &);
int main() {

	char nullChar = '#';
	char tempChar;
	while (cin >> tempChar) {
		cin.putback(tempChar);
		int length = 0;
		char inOrder[1000]; char preOrder[1000];
		cin >> preOrder;
		cin >> inOrder;
		for (int i = 0; preOrder[i] != '\0'; i++) {
			length++;
		}
		BinaryTree<char> tree;
		tree.createByPreInOrder(preOrder, inOrder, length, nullChar);

		tree.postOrder(write); cout << " ";
		tree.levelOrder(write); cout << " ";
		cout << endl;
	}
	return 0;
}
void read(char & elem) {
	cin >> elem;
}
void write(char & elem) {
	cout << elem;
}
bool isNull(char & elem) {
	return elem == '#';
}