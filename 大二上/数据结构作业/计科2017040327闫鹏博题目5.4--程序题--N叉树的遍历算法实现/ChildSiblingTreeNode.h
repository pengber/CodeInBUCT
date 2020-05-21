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
#ifndef CHILDSIBLINGTREENODE_H_INCLUDE
#define	CHILDSIBLINGTREENODE_H_INCLUDE

template <class ElemType>
class ChildSiblingTreeNode {
	ElemType data;
	ChildSiblingTreeNode<ElemType> * leftChild;
	ChildSiblingTreeNode<ElemType> * rightSibling;

	ChildSiblingTreeNode();
	ChildSiblingTreeNode(const ElemType & data, ChildSiblingTreeNode<ElemType> * leftChild = NULL, ChildSiblingTreeNode<ElemType> * rightSibling = NULL);
	virtual ChildSiblingTreeNode();
};
template <class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode() {
	leftChild = NULL;
	rightSibling = NULL;
}
template <class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(const ElemType & data, ChildSiblingTreeNode<ElemType> * leftChild, ChildSiblingTreeNode<ElemType> * rightSibling) {
	this->data = data;
	this->leftChild = leftChild;
	this->rightChild = rightSibling;
}
template <class ElemType>
ChildSiblingTreeNode<ElemType>::~ChildSiblingTreeNode() {
	delete leftChild;
	delete rightSibling;
}
#endif // !CHILDSIBLINGTREENODE_H_INCLUDE
