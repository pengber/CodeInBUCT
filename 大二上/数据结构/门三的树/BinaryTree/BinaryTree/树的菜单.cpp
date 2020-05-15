#include "BinaryTree.h"
using namespace std;

void read(char &);
void write(char &);
bool isNull(char &);
void menu();
int main() {
	BinaryTree<char> tree;
	char nullElem = '#';
	int length = 6;
	char preOrder[100], inOrder[100];
	for (int i = 0; i < length; i++) {
		cin >> preOrder[i];
	}
	for (int i = 0; i < length; i++) {
		cin >> inOrder[i];
	}
	tree.createByPreInOrder(preOrder, inOrder, length, nullElem);
	tree.nonRecurPreOrder(write);
	cout << endl;
	tree.nonRecurPreOrderTwo(tree.getRoot(), write);
	return 0;
	/*BinaryTree<char> tree;
	BinTreeNode<char> * root = tree.getRoot();
	int opeNum;
	char c;
	menu();
	while (cin >> opeNum && opeNum != 0) {
		switch (opeNum)
		{
		case 1:
			tree.preCreate(read, isNull);
			break;
		case 2:
			tree.inCreate(read, isNull);
			break;
		case 3:
			tree.postCreate(read, isNull);
			break;
		case 4:
			tree.preOrder(write);
			break;
		case 5:
			tree.inOrder(write);
			break;
		case 6:
			tree.postOrder(write);
			break;
		default:
			break;
		}
	}

	*/
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

void menu() {
	cout << "请输入操作数:" << endl;
	cout << "0.退出" << endl;
	cout << "1.前序建立二叉树,空结点输入#" << endl;
	cout << "2.中序建立二叉树,空结点输入#" << endl;
	cout << "3.后序建立二叉树,空结点输入#" << endl;
	cout << "4.前序显示二叉树" << endl;
	cout << "5.中序显示二叉树" << endl;
	cout << "6.后序显示二叉树" << endl;
}