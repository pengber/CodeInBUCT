#include <iostream>

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
	cout << "Please input the length:" << endl;
	cin >> length;
	int * elems = new int[length];
	cout << "Please input elems:" << endl;
	for (int i = 1; i <= length; i++) {
		cin >> elems[i];
	}
	cout << "Please input the elem which is finding:" << endl;
	cin >> temp;
	loc = midSearch(elems, length, temp);
	if (!loc) { cout << "It is't here" << endl; }
	else { cout << "The location of this elem is" << loc << endl; }

	system("pause");
	return 0;
}