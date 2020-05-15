#include "Map.h"
#include <iostream>
using namespace std;
#define MAXSIZE 10

int main() {

	BBSTree<MapNode<int,char>> tree;
	MapNode<int,char> * temp = new MapNode<int,char>[MAXSIZE];
	char tempChar;
	for (int i = 0; i < MAXSIZE; i++) {
		cin >> tempChar;
		MapNode<int,char> tempNode(tempChar);
		temp[i] = tempNode;
	}

	for (int i = 0; i < MAXSIZE; i++) {
		tree.insertAVL(temp[i]);
	}
	while (1) {
		cin >> tempChar;
		MapNode<int,char> elem(tempChar);
		if (tree.select(elem)){cout << "there it is!"; }
		else {cout << "no"; }
	}
	system("pause");
	return 0;
}