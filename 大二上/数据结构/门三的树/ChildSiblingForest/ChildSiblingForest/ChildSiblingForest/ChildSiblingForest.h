/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/11/17
************************************************************************************/
/************************************************************************************
*Problem	:
*Tips:		:
************************************************************************************/
/************************************************************************************
*History	:
************************************************************************************/
#ifndef CHILDSIBILINGFOREST
#define CHILDSIBLINGFOREST

#include "BinaryTree.h"
#include "ChildSiblingTreeNode.h"
#include <iostream>
using namespace std;

template <class ElemType>
class ChildSiblingForest {
protected:
	ChildSiblingTreeNode<ElemType> * root;

	void preCreateHelp(ChildSiblingForest<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));

	void destroyHelp(ChildSiblingTreeNode<ElemType> * &root);

	void preOrderHelp(ChildSiblingTreeNode<ElemType> * &root, void(*visit)(ElemType &));

	void postOrderHelp(ChildSiblingTreeNode<ElemType> * &root, void(*visit)(ElemType &));

	void levelOrderHelp(ChildSiblingTreeNode<ElemType> * &root, void(*visit)(ElemType &));

public:
	ChildSiblingForest();

	virtual ~ChildSiblingForest();

	ChildSiblingTreeNode<ElemType> * getFirstChild(ChildSiblingTreeNode<ElemType> * &root) const;

	ChildSiblingTreeNode<ElemType> * getRightSibling(ChildSiblingTreeNode<ElemType> * &root) const;

	void preCreate(void(*visit)(ElemType &), bool (*isNull)(ElemType &));

	void preOrder(void(*visit)(ElemType &));

	void postOrder(void(*visit)(ElemType &));

	void levelOrder(void(*visit)(ElemType &));

	
};
template <class ElmeType>
ChildSiblingForest<ElemType>::ChildSiblingForest() {
	root = NULL;
}
template <class ElemType>
ChildSiblingForest<ElemType>::~ChildSiblingForest() {
	destroyHelp(root->leftChild);
	destroyHelp(root->rightSibling);
	delete root;
}
template <class ElemType>
void ChildSiblingForest<ElemType>::preCreateHelp(ChildSiblingForest<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
	ElemType elem;
	(*visit)(elem);

	if ((*isNull)(elem)) {
		root = NULL;
	}
	else {
		root->data = elem;
		preCreateHelp(root->leftChild, visit, isNull);
		preCreateHelp(root->rightSibling, visit, isNull);
	}
}
template <class ElemType>
void ChildSiblingForest<ElemType>::destroyHelp(ChildSiblingTreeNode<ElemType> * &root) {
	if (root == NULL) {
		return;
	}
	else {
		destroyHelp(root->leftChild);
		destroyHelp(root->rightSibling);
		delete root;
		root = NULL;
	}
}
template <class ElemType>
void ChildSiblingForest<ElemType>::preOrderHelp(ChildSiblingTreeNode<ElemType> * &root, void(*visit)(ElemType &)) {
	if (root == NULL) {
#ifdef SHOW
		std::cout << "#";
#endif // SHOW
		return;
	}
	else {
		(*visit)(root->data);
		for (ChildSiblingTreeNode<ElemType> * child = getFirstChild(root); child != NULL; child = getRightSibling(child)) {
			preOrderHelp(child, visit);
		}
	}
	
}
template <class ElemType>
void ChildSiblingForest<ElemType>::postOrderHelp(ChildSiblingTreeNode<ElemType> * &root, void(*visit)(ElemType &)) {
	if (root == NULL) {
#ifdef SHOW
		std::cout << "#";
#endif // SHOW
		return;
	}
	else {
		for (ChildSiblingTreeNode<ElemType> * child = getFirstChild(root); child != NULL; child = getRightSibling(child)) {
			postOrderHelp(child, visit);
		}
		(*visit)(root->data);
	}
}
template <class ElemType>
void ChildSiblingForest<ElemType>::levelOrderHelp(ChildSiblingTreeNode<ElemType> * root, void(*visit)(ElemType &)) {
	if (root == NULL) {
		return;
	}
	else {
		(*visit)(root->data);
		levelOrderHelp(root->rightSibling, visit);
		levelOrderHelp(root->leftSibling, visit);
	}
}
template <class ElmeType>
ChildSiblingTreeNode<ElemType> * ChildSiblingForest<ElemType>::getFirstChild(ChildSiblingTreeNode<ElemType> * &root) const {
	return root->leftChild;
}
template <class ElemType>
ChildSiblingTreeNode<ElemType> * ChildSiblingForest<ElemType>::getRightSibling(ChildSiblingTreeNode<ElemType> * &root) const {
	return root->rightSibling;
}
template <class ElemType>
void ChildSiblingForest<ElemType>::preCreate(void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
	preCreateHelp(root, visit, isNull);
}
template <class ElemType>
void ChildSiblingForest<ElemType>::preOrder(void(*visit)(ElemType &)) {
	preOrderHelp(root, visit);
}
template <class ElemType>
void ChildSiblingForest<ElemType>::postOrder(void(*visit)(ElemType &)) {
	postOrderHelp(root, visit);
}
template <class ElemType>
void ChildSiblingForest<ElemType>::levelOrder(void(*visit)(ElemType &)) {
	levelOrderHelp(root, visit);
}
#endif // !CHILDSIBILINGFOREST
