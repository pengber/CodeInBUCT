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
#include "BinTreeNode.h"
#include "LinkQueue.h"						//层遍历需要
#include "LinkStack.h"						//非递归遍历需要
#include "assert.h"							//检测申请新空间是否成功需要
#include <typeinfo>							//输出root类型需要
//#define DEBUG								//打开显示函数信息
//#define REMIND							//打开显示提示信息
//#define SHOW								//打开显示空结点
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

	int getHeight() const ;

	BinTreeNode<ElemType> * getRoot() const;

	BinTreeNode<ElemType> * getParent(const BinTreeNode<ElemType> * &cur) const;

	BinTreeNode<ElemType> * getLeftChild(const BinTreeNode<ElemType> * &cur) const;

	BinTreeNode<ElemType> * getRightChild(const BinTreeNode<ElemType> * &cur) const;

	ElemType getElem(BinTreeNode<ElemType> * &cur) const;
	//判：空
	bool isEmpty() const;

	//增
	void insertLeftChild(BinTreeNode<ElemType> * &cur,const ElemType & elem);
	
	void insertRightChild(BinTreeNode<ElemType> * &cur,const ElemType & elem);

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

	int getHeightHelp(BinTreeNode<ElemType> * &root) const ;

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
BinTreeNode<ElemType> * BinaryTree<ElemType>::copyTreeHelp(BinTreeNode<ElemType> * &copy) const{
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
		//throw std::invalid_argument("空结点无双亲结点！") << std::endl;
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
	std::cout << "FUN:" << __func__<< ",LINE:" << __LINE__ << endl;
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
template <class ElemType>
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
template <class ElemType>
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
	return getParentHelp(root,cur);
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getLeftChild(const BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		//throw std::invalid_argument("此结点为空，无左孩子!") << endl;
	}
	else {
		return cur->leftChild;
	}
}
template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::getRightChild(const BinTreeNode<ElemType> * &cur) const {
	if (cur == NULL) {
		//throw std::invalid_argument("此结点为空，无左孩子!") << endl;
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
	preCreateHelp(root,visit, isNull);
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
		std::cout << "node is empty" << std::endl;
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
	
		destroyHelp(this->root);
	
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
