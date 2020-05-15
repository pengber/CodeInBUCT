#ifndef BBSTREE_H_INCLUDE
#define BBSTREE_H_INCLUDE
#include "BBSTNode.h"
#include <stddef.h>							//NULL所需要

#define LH +1								//错误写法:#define LH +1;它会把;也当作LH
#define EH 0
#define RH -1
template <class ElemType>
class BBSTree
{
public:
	BBSTree();
	~BBSTree();
	bool insertAVL(ElemType elem);

	bool select(ElemType elem);
private:
	BBSTNode<ElemType> * root;

	void leftRotate(BBSTNode<ElemType> * & root);

	void rightRotate(BBSTNode<ElemType> * &root);

	void leftBalance(BBSTNode<ElemType> * &root);

	void rightBalance(BBSTNode<ElemType> * &root);

	bool insertAVLHelp(BBSTNode<ElemType> * &root, ElemType elem, bool & taller);

	bool selectHelp(BBSTNode<ElemType> * &root, ElemType elem);

	void destroyHelp(BBSTNode<ElemType> * &root);
};
template <class ElemType>
BBSTree<ElemType>::BBSTree()
{
	root = NULL;
}
template <class ElemType>
BBSTree<ElemType>::~BBSTree()
{
	destroyHelp(this->root);
}
template<class ElemType>
inline bool BBSTree<ElemType>::insertAVL(ElemType elem)
{
	bool taller;
	return insertAVLHelp(this->root, elem, taller);
}
template<class ElemType>
inline bool BBSTree<ElemType>::select(ElemType elem)
{
	return selectHelp(root, elem);
}
template<class ElemType>
inline bool BBSTree<ElemType>::insertAVLHelp(BBSTNode<ElemType>*& root, ElemType elem, bool & taller)
{
	if (!root) {
		root = new BBSTNode<ElemType>(elem);
		taller = true;
	}
	else {
		if (elem == root->data) {
			taller = false;
			return 0;
		}
		if (elem < root->data) {
			if (!insertAVLHelp(root->leftChild, elem, taller)) { 
				return 0;
			}
			if (taller) {
				switch(root->bf)
				{
				case LH:
					leftBalance(root);
					taller = false;
					break;
				case EH: 
					root->bf = LH;
					taller = true;
					break; 
				case RH:
					root->bf = EH;
					taller = false;
					break;
				default:
					break;
				}
				
			}
			
		}
		else {
			if (!insertAVLHelp(root->rightChild, elem, taller)) return 0;
			if (taller) {
				switch (root->bf)
				{
				case LH:
					root->bf = EH;
					taller = false;
					break;
				case EH:
					root->bf = RH;
					taller = true;
					break;
				case RH:
					rightBalance(root);
					taller = false;
					break;
				default:
					break;
				}
			}
		}
	}
	return 1;
}
template<class ElemType>
inline void BBSTree<ElemType>::leftRotate(BBSTNode<ElemType>*& root)
{
	BBSTNode<ElemType> * rc = root->rightChild;
	root->rightChild = rc->leftChild;
	rc->leftChild = root;
	root = rc;
}
template<class ElemType>
inline void BBSTree<ElemType>::rightRotate(BBSTNode<ElemType>*& root)
{
	BBSTNode<ElemType> * lc = root->leftChild;
	root->leftChild = lc->rightChild;
	lc->rightChild = root;
	root = lc;
}
template<class ElemType>
inline void BBSTree<ElemType>::leftBalance(BBSTNode<ElemType>*& root)
{
	BBSTNode<ElemType> * lc = root->leftChild;
	BBSTNode<ElemType> *rc = lc->rightChild;
	switch (lc->bf)
	{
	case LH:
		root->bf = lc->bf = EH;
		rightRotate(root);
		break;
	case RH:
		//BBSTNode<ElemType> *rc = lc->rightChild;
		switch (rc->bf)
		{
		case LH:
			root->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			root->bf = lc->bf = EH;
			break;
		case RH:
			root->bf = EH;
			lc->bf = LH;
			break;
		default:
			break;
		}
		rc->bf = EH;
		leftRotate(root->leftChild);
		rightRotate(root);
		break;
	}
}
template<class ElemType>
inline void BBSTree<ElemType>::rightBalance(BBSTNode<ElemType>*& root)
{
	BBSTNode<ElemType> * rc = root->rightChild;
	BBSTNode<ElemType> * lc = rc->leftChild;
	switch (rc->bf)
	{
		
	case LH:
		//BBSTNode<ElemType> * lc = rc->leftChild;
		switch (lc->bf)
		{
		case LH:
			root->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			root->bf = EH;
			rc->bf = EH;
			break;
		case RH:
			root->bf = LH;
			rc->bf = EH;
			break;
		default:
			break;
		}
		lc->bf = EH;
		rightRotate(root->rightChild);
		leftRotate(root);
		break;
	case RH:
		root->bf = rc->bf = EH;
		leftRotate(root);
		break;
	}
}
template<class ElemType>
inline bool BBSTree<ElemType>::selectHelp(BBSTNode<ElemType>*& root, ElemType elem)
{
	if (!root) { return false; }
	else if (root->data == elem) { return true; }
	else if (root->data > elem) { return selectHelp(root->leftChild, elem); }
	else return selectHelp(root->rightChild, elem);
}
template<class ElemType>
inline void BBSTree<ElemType>::destroyHelp(BBSTNode<ElemType>*& root)
{
	destroyHelp(root->leftChild);
	destroyHelp(root->rightChild);
	delete root;
	root = NULL;
}
#endif // !BBSTREE_H_INCLUDE
