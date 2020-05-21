#include <bits/stdc++.h>
using namespace std;
template <class ElemType,class KeyType>
int midSearch(ElemType elems[], int n, KeyType key) {
	int low = 1; int heigh = n;
	
	while (low <= heigh) {
		int mid = (low + heigh) / 2;
		if (elems[mid] == key) return mid;
		else if (elems[mid] > key) heigh = mid - 1;
		else low = mid + 1;
	}
	return 0;
}
int main() {
	int length;
	int temp;
	int loc;
	cout << "请输入静态表的长度:" << endl;
	cin >> length;
	int * elems = new int[length];
	cout << "请输入静态表的元素:" << endl;
	for (int i = 1; i <= length; i++) {
		cin >> elems[i];
	}
	cout << "请输入要查找的元素:" << endl;
	cin >> temp;
	loc = midSearch(elems, length, temp);
	if (!loc) { cout << "查无此元素!" << endl; }
	else { cout << "此元素位置在:" << loc << endl; }

	system("pause");
	return 0;
}