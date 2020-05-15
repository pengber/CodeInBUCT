#include "ExchangeSort.h"
//#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main() {
	int elems[100];
	int n;
	cout << "请输入需要排序的数字的数目" << endl;
	cin >> n;
	cout << "请输入需要排序的数字:" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> elems[i];
	}
	cout << "排序结果为: " << endl;
	quickSort(elems, n);
	for (int i = 1; i <= n; i++) {
		cout << elems[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}