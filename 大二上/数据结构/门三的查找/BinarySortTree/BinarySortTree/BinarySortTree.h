#ifndef BINARYSORTTREE_H_INCLUDE
#define BINARYSORTTREE_H_INCLUDE

#include "BinTreeNode.h"

template <class ElemType, class KeyType>
class BinarySortTree {
protected:
	BinTreeNode<ElemType> * root;

	bool selectHelp(BinTreeNode<ElemType> * &root, KeyType key, BinTreeNode<ElemType> * &f, BinTreeNode<ElemType> *&p);

	void destroyHelp(BinTreeNode<ElemType> * &root);

public:
	BinarySortTree();

	~BinarySortTree();

	bool select(KeyType key);

	bool insert(ElemType e);
};
template<class ElemType, class KeyType>
inline bool BinarySortTree<ElemType, KeyType>::selectHelp(BinTreeNode<ElemType>*& root, KeyType key, BinTreeNode<ElemType>*& f, BinTreeNode<ElemType>*& p)
{
	if (!root) { p = f; return false;}
	else if (root->data == key) { p = root; return true; }
	else if (root->data > key) { return selectHelp(root->leftChild, key, root, p); }
	else return selectHelp(root->rightChild, key, root, p);
}
template<class ElemType, class KeyType>
inline void BinarySortTree<ElemType, KeyType>::destroyHelp(BinTreeNode<ElemType>*& root)
{
	if (root != NULL) {
		destroyHelp(root->leftChild);
		destroyHelp(root->rightChild);
		delete root;
		root = NULL;
	}
}
template<class ElemType, class KeyType>
inline BinarySortTree<ElemType, KeyType>::BinarySortTree()
{
	root = NULL;
}
template<class ElemType, class KeyType>
inline BinarySortTree<ElemType, KeyType>::~BinarySortTree()
{
	destroyHelp(root);
}
template<class ElemType, class KeyType>
inline bool BinarySortTree<ElemType, KeyType>::select(KeyType key)
{
	BinTreeNode<ElemType> * p;
	BinTreeNode<ElemType> * f = NULL;
	return selectHelp(this->root, key, f, p);
}
template<class ElemType, class KeyType>
inline bool BinarySortTree<ElemType, KeyType>::insert(ElemType e)
{
	BinTreeNode<ElemType> * p;
	BinTreeNode<ElemType> * f = NULL;
	if (!selectHelp(this->root, e, f, p)) {
		BinTreeNode<ElemType> * newNode = new BinTreeNode<ElemType>(e);

		if (!p) this->root = newNode;
		else if (e < p->data) { p->leftChild = newNode; }
		else p->rightChild = newNode;
		return true;
	}
	return false;
}

#endif // !BINARYSORTTREE_H_INCLUDE
