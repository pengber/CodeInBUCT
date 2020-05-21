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
#ifndef BBSTNODE_H_INCLUDE
#define BBSTNODE_H_INCLUDE
#include <stddef.h>
template <class ElemType>
struct BBSTNode {
	ElemType data;
	int bf;
	BBSTNode<ElemType> * leftChild;
	BBSTNode<ElemType> * rightChild;

	BBSTNode();
	BBSTNode(const ElemType & data, BBSTNode<ElemType> * leftChild = NULL,
		BBSTNode<ElemType> * rightChild = NULL, int bf = 0);
	virtual ~BBSTNode();
};

template <class ElemType>
BBSTNode<ElemType>::BBSTNode() {
	leftChild = rightChild = NULL;
	bf = 0;
}

template <class ElemType>
BBSTNode<ElemType>::BBSTNode(const ElemType & data, BBSTNode<ElemType> * leftChild,
	BBSTNode<ElemType> * rightChild,int bf) {

	this->data = data;
	this->leftChild = leftChild;
	this->rightChild = rightChild;
	this->bf = bf;
}

template <class ElemType>
BBSTNode<ElemType>::~BBSTNode() {
	delete leftChild;
	delete rightChild;
}
#endif