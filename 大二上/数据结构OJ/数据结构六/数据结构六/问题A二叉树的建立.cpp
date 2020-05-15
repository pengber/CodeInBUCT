#include <bits/stdc++.h>
#include "BinaryTree.h"
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
class BinaryTree {
protected:
	BinTreeNode<ElemType> * root;

	void preCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
	void preOrderHelp(BinaryTree <ElemType>* &root, void(*visit)(ElemType &));
	void inOrderHelp(BinaryTree <ElemType>* &root, void(*visit)(ElemType &));
	void postOrderHelp(BinaryTree <ElemType> * &root, void(*visit)(ElemType &));
	void levelOrderHelp(BinaryTree <ElemType> * &root, void(*visit)(ElemType &));

public:
	BinaryTree();

	void preCreate(void(*visit)(ElemType &), vool(*isNull)(ElemType &));
	void preOrder(void(*visit)(ElemType &));
	void inOrder(void(*visit)(ElemType &));
	void postOrder(void(*visit)(ElemType &));
	void levelOrder(void(*visit)(ElemType &));
};
template <class ElemType>
BinaryTree<ElemType>::BinaryTree() {
	root = NULL;
}
template <class ElemType>
void BinaryTree<ElemType>::preCreateHelp(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &)) {
	ElemType 
}
void read(char &);
void write(char &);
bool isNull(char &);
int main() {
	BinaryTree<char> tree;
	int nullChar = '#';
	tree.preCreate(read, isNull);

	tree.inOrder(write); cout << " ";
	tree.postOrder(write); cout << " ";
	tree.levelOrder(write); cout << " ";
	cout << endl;
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