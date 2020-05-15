#include <bits/stdc++.h>
using namespace std;

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

	BinTreeNode<ElemType> * getRoot();

	int getHeight(BinTreeNode<ElemType> * &root);
};
template<class ElemType, class KeyType>
inline bool BinarySortTree<ElemType, KeyType>::selectHelp(BinTreeNode<ElemType>*& root, KeyType key, BinTreeNode<ElemType>*& f, BinTreeNode<ElemType>*& p)
{
	if (!root) { p = f; return false; }
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
template<class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::getHeight(BinTreeNode<ElemType>*& root)
{
	int height = 0;
	if (!root) {
		height = 0;
	}
	else {
		int leftHeight = getHeight(root->leftChild);
		int rightHeight = getHeight(root->rightChild);
		height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
	}

	return height;
}
template <class ElemType, class KeyType>
BinTreeNode<ElemType> * BinarySortTree<ElemType, KeyType>::getRoot() {
	return this->root;
}
#define INFINITY 100000

int main() {
	int n, m, tempElem;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int elems[101];
		int weight[101];
		int min = INFINITY, k, pos;
		BinarySortTree<int, int> tree;
		cin >> m;

		for (int j = 0; j < m; j++) {
			cin >> elems[j];
		}
		for (int j = 0; j < m; j++) {
			cin >> weight[j];
		}

		for (int j = 0; j < m; j++) {
			for (k = 0; k < m; k++) {
				if (weight[k] < min) {
					min = weight[k];
					pos = k;
				}
			}
			tree.insert(elems[pos]);
			weight[pos] = INFINITY;
			min = INFINITY;
		}
		BinTreeNode<int> * root = tree.getRoot();
		cout << tree.getHeight(root) << endl;
	}
	return 0;
}

