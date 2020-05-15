#include "BBSTree.h"
#include <iostream>
using namespace std;

int main() {
	BBSTree<int> tree;
	int m, n;
	int temp;
	
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		cin >> temp;
		tree.insertAVL(temp);
	}
	for (int i = 0; i < n; i++) {
		cin >> temp;
		if (tree.select(temp)) cout << 1 << endl;
		else cout << 0 << endl;
	}
	system("pause");
	return 0;
}