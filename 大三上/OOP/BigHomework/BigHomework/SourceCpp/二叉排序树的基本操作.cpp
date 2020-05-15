#include <bits/stdc++.h>
#include "BinarySortTree.h"
using namespace std;
int main() {
	BinarySortTree<int, int> tree;
	int m, n;
	int temp;
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		cin >> temp;
		tree.insert(temp);
	}

	for (int i = 0; i < n; i++) {
		cin >> temp;
		if (tree.select(temp)) cout << 1 << " ";
		else cout << 0 << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}