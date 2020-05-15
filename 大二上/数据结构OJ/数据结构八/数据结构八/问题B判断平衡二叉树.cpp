#include <bits/stdc++.h>

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
	//delete leftChild;
	//delete rightChild;
}


template <class ElemType>
class BinaryTree {

public:
	BinTreeNode<ElemType> * root;
	int flag = true;

	BinaryTree();
	~BinaryTree();
	void preCreate(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &));
	int getHeight(BinTreeNode<ElemType> * root);
	bool isBalance();
	void destroy(BinTreeNode<ElemType> * &root);

};

template<class ElemType>
BinaryTree<ElemType>::BinaryTree()
{
	root = NULL;
}
template<class ElemType>
BinaryTree<ElemType>::~BinaryTree()
{
	destroy(this->root);
}
template<class ElemType>
void BinaryTree<ElemType>::preCreate(BinTreeNode<ElemType> * &root, void(*visit)(ElemType &), bool(*isNull)(ElemType &))
{
	ElemType elem;
	(*visit)(elem);

	if ((*isNull)(elem)) {
		root = NULL;
	}
	else
	{
		root = new BinTreeNode<ElemType>(elem);
		preCreate(root->leftChild, visit, isNull);
		preCreate(root->rightChild, visit, isNull);
	}
}
template<class ElemType>
int BinaryTree<ElemType>::getHeight(BinTreeNode<ElemType>* root)
{
	int height = 0;
	if (!root) {
		height = 0;
	}
	else {
		int leftHeight = getHeight(root->leftChild);
		int rightHeight = getHeight(root->rightChild);
		int absHeight = leftHeight - rightHeight;
		if (abs(absHeight) > 1) flag = false;

		height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
	}

	return height;
}
template<class ElemType>
bool BinaryTree<ElemType>::isBalance()
{
	if (flag) return true;
	else return false;
}
template<class ElemType>
void BinaryTree<ElemType>::destroy(BinTreeNode<ElemType>*& root)
{
	if (!root) {
		return;
	}
	else {
		destroy(root->leftChild);
		destroy(root->rightChild);
		delete root;
	}
}

using namespace std;

void read(char & e) {
	cin >> e;
}
bool isNull(char & e) {
	if (e == '#') {
		return true;
	}
	else return false;
}

int main() {
	char elem;

	while (cin >> elem) {
		cin.putback(elem);
		BinaryTree<char> tree;
		tree.preCreate(tree.root, read, isNull);
		tree.getHeight(tree.root);
		if (tree.flag) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

}