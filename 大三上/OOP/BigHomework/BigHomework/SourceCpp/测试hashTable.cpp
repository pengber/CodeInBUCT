#include "HashTable.h"
#include <iostream>
using namespace std;

int main() {
	int n, m, temp, temp2;
	int k;
	cin >> n >> m >> k;
	HashTable<int, int> table(n,m);
	for (int i = 0; i < n; i++) {
		cin >> temp;
		table.insert(temp);
	}
	for (int i = 0; i < k; i++) {
		cin >> temp2;
		if (table.select(temp2, temp)) cout << 1 << " ";
		else cout << 0 << " ";

	}
	system("pause");
	return 0;
}



