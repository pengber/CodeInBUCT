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