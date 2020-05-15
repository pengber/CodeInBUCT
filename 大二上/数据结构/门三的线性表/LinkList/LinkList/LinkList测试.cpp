#include "LinkList.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	LinkList<int> list;
	int elem;
	list.insertElem(1, 1);
	list.insertBehindAll(2);
	list.deteleElem(1, elem);
	list.setElem(1, 3);
	list.deteleElem(3, elem);
	list.display();
	getchar();
	return 0;
}