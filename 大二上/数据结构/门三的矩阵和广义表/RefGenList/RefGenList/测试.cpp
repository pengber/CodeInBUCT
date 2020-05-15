#include "RefGenList.h"
#include <iostream>
using namespace std;

int main() {
	RefGenList<char> list;				//这个得用char,而不是int,用int的话字符型输入不进去Int cin >> atomData;
	list.input();
	cout << list.getDepth();
	system("pause");
	return 0;
}