#include <iostream>
#include "SimpleLinkList.h"
using namespace std;
void pri(SimpleLinkList<int> & simpleLinkList) {
	int tempElem;

	for (int i = 1; i <= simpleLinkList.getLength(); i++) {
		simpleLinkList.getElem(i, tempElem);
		cout << tempElem << " " << endl;
	}
}
int main() {
	SimpleLinkList<int> simpleLinkListA;
	int tempElem, length = 0, tempPos;
	for (int i = 1; i <= 10; i++) {
		simpleLinkListA.insertAfterAll(i);
	}

	//得
	cout << simpleLinkListA.getLength() << endl;
	simpleLinkListA.getElem(1,tempElem);
	cout << tempElem << endl;
	simpleLinkListA.getElemPos(tempPos, 11);
	cout << tempPos << endl;
	cout << simpleLinkListA.getLength() << endl;

	//判
	if (simpleLinkListA.isEmpty()) cout << "空" << endl;
	else cout << "非空" << endl;

	//增
	simpleLinkListA.insertAfterAll(11);
	//pri(simpleLinkListA);
	simpleLinkListA.insertBeforeAll(0);
	simpleLinkListA.insert(14, 12);
	//pri(simpleLinkListA);

	//改
	simpleLinkListA.setElem(15, 111);
	pri(simpleLinkListA);

	//删除
	cout << "链表现在如下" << endl;
	pri(simpleLinkListA);
	cout << "链表长度" << simpleLinkListA.getLength() << endl;
	simpleLinkListA.deleteElemByVal(1);
	pri(simpleLinkListA);
	cout << "测试赋值构造函数" << endl;
	SimpleLinkList<int> simpleLinkListB(simpleLinkListA);
	pri(simpleLinkListB);
	cout << "测试重载运算符" << endl;
	SimpleLinkList<int> simpleLinkListC;
	simpleLinkListC = simpleLinkListA;
	pri(simpleLinkListC);
	return 0;

}