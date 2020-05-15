/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/11/6
************************************************************************************/
/************************************************************************************
*Problem	:
*Tips:		:
************************************************************************************/
/************************************************************************************
*History	:
************************************************************************************/
#ifndef BINTREENODE_H_INCLUDE
#define BINTREENODE_H_INCLUDE
#include <cstddef>
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
/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/11/17
************************************************************************************/
/************************************************************************************
*Problem	:
√1.没搞清楚为什么求双亲结点需要辅助函数递归求解，求左右孩子就不用了
2.deleteNodeHelp没打
3.前序非递归遍历的空结点输出没打,层次遍历也没有输出空节点
4.不清楚getHeight(const BinTreeNode<ElemType> * &root) const的显示错误
*Tips:		:
1.Q:为什么要设置辅助函数?
A:比如说对外接口是int getNodeCount() const,辅助函数是int getNodeCount(BinTreeNode
* root) const;在对外接口里面调用return getNodeCount(this->root)。主程序调用直接
obj.getNodeCount（）多么方便，就不在需要填写参数了。

************************************************************************************/
/************************************************************************************
*History	:
************************************************************************************/
#pragma once

#include <stdexcept>
#include <exception>
#include <iostream>
//#include "BinTreeNode.h"
//#include "LinkQueue.h"						//层遍历需要
//#include "LinkStack.h"						//非递归遍历需要
#include "assert.h"							//检测申请新空间是否成功需要
#include <typeinfo>							//输出root类型需要
//#define DEBUG								//打开显示函数信息
//#define REMIND							//打开显示提示信息
//#define SHOW								//打开显示空结点
using namespace std;
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

	void createByPreInOrder(ElemType * preOrder, ElemType * inOrder, int length, ElemType & nullElem);


	//改
	bool setElem(BinTreeNode<ElemType> * &cur, const ElemType & elem);

	bool serRoot(BinTreeNode<ElemType> * &cur);

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
	//非递归遍历
	void nonRecurPreOrder(void(*visit)(ElemType &));

	void nonRecurInOrder(void(*visit)(ElemType &));

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
		throw std::invalid_argument("空结点无双亲结点！");
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
		root = new BinTreeNode<ElemType>(nullElem);
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
/*template <class ElemType>
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
*/
/*template <class ElemType>
void BinaryTree<ElemType>::nonRecurPreOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) {
	BinTreeNode<ElemType> * cur = root;
	LinkStack<BinTreeNode<ElemType> *> stack;

	while (cur != NULL) {
		(*visit)(cur->data);
		stack.push(cur);

		if (cur->leftChild != NULL) {
			cur = cur->leftChild;
		}
		else if (!stack.isEmpty()) {
			while (!stack.isEmpty()) {
				stack.pop(cur);
				cur = cur->rightChild;
				if (cur != NULL) break;
			}
		}
		else {
			cur = NULL;
		}
	}
}
*/
/*template <class ElemType>
void BinaryTree<ElemType>::nonRecurInOrderHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &)) {
	BinTreeNode<ElemType> * cur = root;
	LinkStack<BinTreeNode<ElemType> *> stack;

	while (cur || !stack.isEmpty()) {
		if (cur) {
			stack.push(cur);
			cur = cur->leftChild;
		}
		else {
#ifdef SHOW
			std::cout << '#';
#endif // SHOW
			stack.pop(cur);
			(*visit)(cur->data);
			cur = cur->rightChild;
		}
	}
#ifdef SHOW
	std::cout << '#';
#endif // SHOW

}
*/
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
		throw std::invalid_argument("此结点为空，无左孩子!");
	}
	else {
		return cur->leftChild;
	}
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getRightChild(const BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		throw std::invalid_argument("此结点为空，无左孩子!");
	}
	else {
		return cur->rightChild;
	}
}
template <class ElemType>
ElemType BinaryTree<ElemType>::getElem(BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		throw std::invalid_argument("结点为空，没有值！\n");
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
		throw std::invalid_argument("结点为空，不能插入左孩子！\n");
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
		throw std::invalid_argument("结点为空，不能插入右孩子!\n");
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
void BinaryTree<ElemType>::createByPreInOrder(ElemType * preOrder, ElemType * inOrder, int length, ElemType & nullElem) {
	createByPreInOrderHelp(root, preOrder, inOrder, length, nullElem);
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
template<class ElemType>
bool BinaryTree<ElemType>::serRoot(BinTreeNode<ElemType>*& cur)
{
	this->root = cur;
	return true;
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
		throw std::invalid_argument("结点为空，不能删除左子树！\n");
	}
	else {
		destroyHelp(cur->leftChild);
	}
}
template <class ElemType>
void BinaryTree<ElemType>::deleteRightChildTree(BinTreeNode<ElemType> * &cur) {
	if (cur == NULL) {
		throw std::invalid_argument("结点为空，不能删除右子树！\n");
	}
	else {
		destroyHelp(cur->rightChild);
	}
}
template<class ElemType>
inline void BinaryTree<ElemType>::destroy()
{
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
template <class ElemType>
void BinaryTree<ElemType>::nonRecurPreOrder(void(*visit)(ElemType &)) {
	nonRecurPreOrderHelp(root, visit);
}
template <class ElemType>
void BinaryTree<ElemType>::nonRecurInOrder(void(*visit)(ElemType &)) {
	nonRecurInOrderHelp(root, visit);
}
/*================================特征函数实现完毕=============================*/



#include <iostream>
#include <stdexcept>							//out_of_range需要
#include <iomanip>							//display函数需要
//#include "LinkQueue.h"						//深度优先搜索需要
#include "assert.h"
using namespace std;
#define INFINITY 1000						//自己连自己的和无连接的都为INFINITY
#ifndef INVISITED_DEFINE_INCLUDE
#define INVISITED_DEFINE_INCLUDE
#define UNVISITED false
#define VISITED	true
#endif
int low[1000] = { 0 };
int visited[1000] = { 0 };
int countt = 0;
int order[1000] = { 0 };
int index = 0;
//#define REMIND
//#define DEBUG
template <class ElemType>
class AdjMatrixUndirGraph {
public:
	AdjMatrixUndirGraph();
	AdjMatrixUndirGraph(ElemType * vertex, int vexNum);
	~AdjMatrixUndirGraph();
	//特征函数
	//得
	int getVertexCount();					//得到顶点数目

	int getEdgeCount();						//得到边的数目

	int getVertex(ElemType & elem);			//得到元素在原图中得位置

	ElemType getVertexElem(int vertex);		//得到顶点元素值

	bool getVisited(int vertex);			//得到结点访问信息

	int getFirstAdjVertex(int vertex);		//得到vertex的第一个邻接点

	int getNextAdjVertex(int vertex1, int vertex2);			//得到vertex1相对于vertex2的第一个临界点
															//判
															//插
	bool insertEdge(int vertex1, int vertex2);

	//改
	void setGraph(ElemType * vertex, int vexNum);

	bool setElem(int vertex, ElemType elem);

	bool setVisited(int vertex);
	//删
	bool deleteEdge(int vertex1, int vertex2);

	//遍历
	void DFSTraverse(int vertex, void(*visit)(ElemType &));

	void BFSTraverse(int vertex, void(*visit)(ElemType &));
	//特殊函数
	void display();

	void FindArticul();

	void DFSArticul(int vertext);

	void DFSForest(BinaryTree<ElemType> * &forest);

	void DFSTree(BinTreeNode<ElemType> * &root, ElemType vex);
protected:
	int m_vertexSize;						//顶点个数
	int m_edgeSize;							//边数
	int **m_matrix;						//邻接矩阵
	mutable bool * m_visited;				//是否访问过标志位
	ElemType * m_elems;

	void destroyGraphHelp();

	void DFSHelp(int vertex, void(*visit)(ElemType &));
	void BFSHelp(int vertex, void(*visit)(ElemType &));
};
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::destroyGraphHelp() {
	delete[] m_elems;
	m_elems = NULL;

	delete[] m_visited;
	m_visited = NULL;

	for (int i = 0; i < m_vertexSize; i++) {
		delete[] m_matrix[i];
	}
	delete[] m_matrix;
	m_matrix = NULL;
}
//函数名称: void DFSHelp(int vertex, void(*visit)(ElemType &))
//函数功能: 深度优先搜索辅助函数
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSHelp(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不正确!");
	}
	if (m_visited[vertex] == UNVISITED) {
		ElemType elem = this->getVertexElem(vertex);
		(*visit)(elem);
		this->m_visited[vertex] = VISITED;
	}
	int vextemp;
	for (vextemp = this->getFirstAdjVertex(vertex); vextemp != -1; vextemp = this->getNextAdjVertex(vertex, vextemp)) {
		if (this->m_visited[vextemp] == UNVISITED) {
			DFSHelp(vextemp, visit);
		}
	}

}
//函数名称: void BFSHelp(int vertex, void(*visit)(ElemType &))
//函数功能: 实现广度优先搜索
/*template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::BFSHelp(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
if (m_visited[vertex] == UNVISITED) {
ElemType elem = this->getVertexElem(vertex);
(*visit)(elem);
this->setVisited(vertex);
}

LinkQueue<int> queue;
int vexTemp;
queue.inQueue(vertex);
ElemType elem;
while (!queue.isEmpty()) {
queue.outQueue(vertex);

for (vexTemp = this->getFirstAdjVertex(vertex);
vexTemp != -1;
vexTemp = this->getNextAdjVertex(vertex, vexTemp))
{
if (this->m_visited[vexTemp] == UNVISITED) {
this->m_visited[vexTemp] = VISITED;
elem = getVertexElem(vexTemp);
(*visit)(elem);
queue.inQueue(vexTemp);
}
}
}
}
*/
/***********************************基本成员函数实现**********************************/
/*
int getVertexCount();					//得到顶点数目
int getEdgeCount();						//得到边的数目
int getVertex(ElemType * elem);			//得到元素在原图中得位置
ElemType getVertexElem(int vertex);		//得到顶点元素值
bool getVisited(int vertex);			//得到结点访问信息
int getFirstAdjVertex(int vertex);		//得到vertex的第一个邻接点
int getNextAdjVertex(int vertex1, int vertex2)				//得到vertex1相对于vertex2的第一个临界点
bool insertEdge(int vertex1, int vertex2);
void setGraph(ElemType * vertex, int vexNum);
bool setElem(int vertex, ElemType elem);
bool setVisited(int vertex);
bool deleteEdge(int vertex1, int vertex2);
void DFSTraverse(int vertex, void(*visit)(ElemType &));
void BFSTraverse(int vertex, void(*visit)(ElemType &));
*/
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph() {
	this->m_vertexSize = 0;
	this->m_edgeSize = 0;
	this->m_elems = NULL;
	this->m_visited = NULL;
	this->m_matrix = NULL;
}
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType * vertex, int vexNum) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vexNum < 0) {
		throw std::out_of_range("vexNum参数不能为负数!");
	}
	this->m_vertexSize = vexNum;
	this->m_edgeSize = 0;

	this->m_elems = new ElemType[m_vertexSize];
	assert(this->m_elems);
	this->m_visited = new bool[m_vertexSize];
	assert(this->m_visited);
	this->m_matrix = (int **)new int *[m_vertexSize];

	for (int i = 0; i < m_vertexSize; i++) {
		m_elems[i] = vertex[i];
		m_visited[i] = UNVISITED;
		m_matrix[i] = new int[m_vertexSize];
		assert(m_matrix[i]);
	}
	int i; int j;
	for (i = 0; i < m_vertexSize; i++) {
		for (j = 0; j < m_vertexSize; j++) {
			m_matrix[i][j] = INFINITY;
		}
	}
}
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	destroyGraphHelp();
}
/*===================================基本成员函数实现完毕============================*/
/************************************特征成员函数实现********************************/
//函数名称: int getVertexCount()
//函数功能: 返回顶点个数
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getVertexCount() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	return m_vertexSize;
}
//函数名称: int getEdgeCount()
//函数功能: 返回边数
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getEdgeCount() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	return m_edgeSize;
}
//函数名称: int getVertex(ElemType & elem)
//函数功能: 返回元素的顶点位置,若无,则返回-1;
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getVertex(ElemType & elem) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = 0; i < this->m_vertexSize; i++) {
		if (this->m_elems[i] == elem) {
			return i;
		}
	}
	return -1;
}
//函数名称: ElemType getVertexElem(int vertex)
//函数功能: 返回顶点元素值
template <class ElemType>
ElemType AdjMatrixUndirGraph<ElemType>::getVertexElem(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}

	return this->m_elems[vertex];
}
//函数名称: bool getVisited(int vertex)
//函数功能: 得到某顶点的访问信息
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::getVisited(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}
	return m_visited[vertex];
}
//函数名称: int getFirstAdjVertex(int vertex)
//函数功能:	返回vertex的第一个邻接点
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getFirstAdjVertex(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}
	for (int i = 0; i < m_vertexSize; i++) {
		if (m_matrix[vertex][i] != INFINITY) {
			return i;
		}
	}
	return -1;
}
//函数名称: int getNextAdjVertex(int vertex1, int vertex2) 
//函数功能: 返回vertex1行和vertex2+1列以后的邻接顶点
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getNextAdjVertex(int vertex1, int vertex2) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1和vertex2不能相等!");
	}

	for (int i = vertex2 + 1; i < m_vertexSize; i++) {
		if (m_matrix[vertex1][i] != INFINITY) {
			return i;
		}
	}
	return -1;
}
//函数名称: bool insertEdge(int vertex1, int vertex2) 
//函数功能: 在vertex1与vertex2之间插入边
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::insertEdge(int vertex1, int vertex2) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1不能等于vertex2!");
	}

	if (this->m_matrix[vertex1][vertex2] == INFINITY) {
		this->m_matrix[vertex1][vertex2] = 1;
		this->m_matrix[vertex2][vertex1] = 1;
		m_edgeSize++;
		return true;
	}
	else {
#ifdef REMIND
		std::cout << "两顶点已经有边,不能设置边了!" << std::endl;
#endif // REMIND
		return false;						//这个返回false我觉得返回的没有意义
	}
}
//函数名称: void setGraph(ElemType * vertex, int vexNum)
//函数功能: 重新设置图的顶点元素和个数,将边置为0
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::setGraph(ElemType * vertex, int vexNum) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	destroyGraphHelp();

	if (vexNum < 0) {
		throw std::out_of_range("vexNum参数不能为负数!");
	}
	this->m_vertexSize = vexNum;
	this->m_edgeSize = 0;

	this->m_elems = new ElemType[m_vertexSize];
	assert(this->m_elems);
	this->m_visited = new bool[m_vertexSize];
	assert(this->m_visited);
	this->m_matrix = (int **)new int *[m_vertexSize];

	for (int i = 0; i < m_vertexSize; i++) {
		m_elems[i] = vertex[i];
		m_visited[i] = UNVISITED;
		m_matrix[i] = new int[m_vertexSize];
		assert(m_matrix[i]);
	}
	int i; int j;
	for (i = 0; i < m_vertexSize; i++) {
		for (j = 0; j < m_vertexSize; j++) {
			m_matrix[i][j] = INFINITY;
		}
	}
}
//函数名称: bool setElem(int vertex, ElemType elem)
//函数功能: 设置顶点元素,参数范围不合法返回false
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::setElem(int vertex, ElemType elem) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
#ifdef REMIND
		std::cout << "vertex参数范围不合法!" << std::endl;
#endif // REMIND
		return false;
	}
	else {
		m_elems[vertex] = elem;
		return true;
	}
}
//函数名称: bool setVisited(int vertex)
//函数功能: 设置vertex为访问过,已经为访问过的返回假
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::setVisited(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
		throw std::out_of_range("vertex参数不合法!");
	}

	if (m_visited[vertex] == VISITED) {
#ifdef REMIND
		std::cout << "该顶点已经访问过,返回假!" << endl;
#endif // REMIND
		return false;
	}
	else {
		m_visited[vertex] = VISITED;
		return true;
	}
}
//函数名称: bool deleteEdge<int vertex1, int vertex2)
//函数功能: 删除vertex1指向vertex2之间的边,没有边返回失败
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::deleteEdge(int vertex1, int vertex2) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1不能等于vertex2!");
	}

	if (m_matrix[vertex1][vertex2] != INFINITY) {
		m_matrix[vertex1][vertex2] = INFINITY;
		m_matrix[vertex2][vertex1] = INFINITY;
		m_edgeSize--;
		return true;
	}
	else {
#ifdef REMIND
		std::cout << "vertex1与vertex2原本就没有边!无法删除!" << std::endl;
#endif // REMIND
		return false;
	}
}
//函数名称: void DFSTraverse(int vertex, void(*visit)(ElemType &))
//函数功能: 深度优先搜索
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSTraverse(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = vertex; i < m_vertexSize; i++) {
		DFSHelp(i, visit);
	}
}
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::BFSTraverse(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = vertex; i < m_vertexSize; i++) {
		BFSHelp(i, visit);
	}
}
/*=================================特征成员函数实现完毕===============================*/
//函数名称: void display()
//函数功能: 显示图的信息
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::display() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	std::cout << "此图的顶点数:" << this->getVertexCount() << "个" << std::endl;
	std::cout << "此图的边数:" << this->getEdgeCount() << "条" << std::endl;
	/*****************输出邻接矩阵的列标*************/
	std::cout << "\\";
	for (int i = 0; i < m_vertexSize; i++) {
		std::cout << std::setw(4) << m_elems[i];
	}
	std::cout << std::endl;
	/*==============================================*/
	/***************输出邻接矩阵的行标和矩阵*********/
	for (int i = 0; i < m_vertexSize; i++) {
		std::cout << m_elems[i];
		for (int j = 0; j < m_vertexSize; j++) {
			std::cout << std::setw(4) << m_matrix[i][j];
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	/*=============================================*/
}
template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::FindArticul()
{
	countt = 1;
	visited[0] = 1;

	for (int i = 1; i < m_vertexSize; i++) {
		visited[i] = 0;
	}
	int v = this->getFirstAdjVertex(0);
	DFSArticul(v);

	if (countt < this->m_vertexSize) {
		order[index++] = 0;
		for (v = this->getFirstAdjVertex(0); v != -1; v = this->getNextAdjVertex(0, v)) {
			if (visited[v] == 0) {
				DFSArticul(v);
			}
		}
	}
	std::cout << index << std::endl;
	int temp;
	for (int i = 0; i < index - 1; i++) {
		for (int j = 0; j < index - 1 - i; j++) {
			if (order[j] > order[j + 1]) {
				temp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < index; i++) {
		std::cout << order[i] << " ";
	}
}
template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSArticul(int vertex) {
	int min = ++countt;
	visited[vertex] = min;

	int vexTemp;
	for (vexTemp = this->getFirstAdjVertex(vertex); vexTemp != -1; vexTemp = this->getNextAdjVertex(vertex, vexTemp)) {
		if (visited[vexTemp] == 0) {
			DFSArticul(vexTemp);
			if (low[vexTemp] < min) min = low[vexTemp];
			if (low[vexTemp] >= visited[vertex]) order[index++] = vertex;
		}
		else if (visited[vexTemp] < min) min = visited[vexTemp];
	}

	low[vertex] = min;
}
template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSForest(BinaryTree<ElemType> * &forest)
{
	BinTreeNode<ElemType> * q = NULL;
	for (int i = 0; i < m_vertexSize; i++) {
		m_visited[i] = false;
	}
	bool first = true;
	for (int i = 0; i < m_vertexSize; i++) {
		if (!m_visited[i]) {
			BinTreeNode<ElemType> * p = new BinTreeNode<ElemType>(m_elems[i]);
			if (first) {
				forest->serRoot(p);
				first = false;
			}
			else {
				q->rightChild = p;
			}
			q = p;
			this->DFSTree(p, m_elems[i]);
			cout << endl;
		}

	}
}
template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSTree(BinTreeNode<ElemType>*& root, ElemType vex)
{
	m_visited[vex] = true;
	bool first = true;
	BinTreeNode<ElemType> * q = root;
	std::cout << vex << " ";
	for (int k = this->getFirstAdjVertex(vex); k != -1; k = this->getNextAdjVertex(vex, k)) {

		if (!m_visited[k]) {
			BinTreeNode<ElemType> * newNode = new BinTreeNode<ElemType>(k);

			if (first) {
				root->leftChild = newNode;
				first = false;
			}
			else {
				q->rightChild = newNode;
			}
			q = newNode;
			
			DFSTree(q, k);
		}
	}
}

void write(int &);
using namespace std;
int main() {
	AdjMatrixUndirGraph<int> graph;
	BinaryTree<int> * forest = new BinaryTree<int>;
	int length, temp;
	int vertex[1000];
	cin >> length;
	for (int i = 0; i < length; i++) {
		vertex[i] = i;
	}
	graph.setGraph(vertex, length);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cin >> temp;
			if (temp != 0) {
				graph.insertEdge(i, j);
			}
		}
	}

	graph.DFSForest(forest);

	system("pause");
	return 0;

}

void write(int & elem) {
	cout << elem;
}