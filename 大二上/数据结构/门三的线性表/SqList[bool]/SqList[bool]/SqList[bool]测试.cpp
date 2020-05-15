#include <iostream>
#include "SqList[bool].h"
using namespace std;

void pri(SqList<int> & list) {
	cout << "线性表信息如下:" << endl;
	cout << "length:" << list.getLength() << endl;
	cout << "capacity:" << list.getCapacity() << endl;
	int temp;
	for (int i = 1; i <= list.getLength(); i++) {
		list.getElem(i, temp);
		cout << "第" << i << "个元素值为:" << temp << endl;
	}
}

int main() {
	SqList<int> list(100);
	int temp, tempPos;
	for (int i = 1; i <= 80;i++) {
		list.insert(i, i);
	}
	//得
	cout << "线性表的长度为:" << list.getLength() << endl;
	cout << "线性表的容量为:" << list.getCapacity() << endl;
	for (int i = 1; i <= list.getLength(); i++) {
		list.getElem(i, temp);
		cout << "线性表的元素为:" << temp << endl;
	}
	//判
	if (list.isEmpty()) cout << "线性表为空" << endl;
	if (list.isExitByVal(tempPos, 40)) cout << "40存在与线性表中,位置" << tempPos << endl;
	//增
	list.insertBehindAll(100);
	list.getElem(list.getLength(), temp);
	cout << "线性表最后一个元素为" << temp << endl;
	//改
	list.setElem(list.getLength(), 101);
	pri(list);
	list.reset(200);
	pri(list);
	//增
	list.insertBehindAll(1);
	list.insertBehindAll(2);
	pri(list);
	//删
	list.deleteElem(1, temp);
	pri(list);
	list.clean();
	pri(list);

	//友元函数
	cout << "测试友元函数" << endl;
	SqList<int> listA, listB;
	listA.insertBehindAll(1);
	listA.insertBehindAll(2); 
	listA.insertBehindAll(3);
	listA.insertBehindAll(4);
	listA.insertBehindAll(5);

	listB.insertBehindAll(3);
	listB.insertBehindAll(4);
	listB.insertBehindAll(5);
	listB.insertBehindAll(6);
	listB.insertBehindAll(7);
	SqList<int> listC(listA.getLength() + listB.getLength());

	Common(listA, listB, listC);
	pri(listC);
	SqList<int> listD(listA.getLength() + listB.getLength());
	Union(listA, listB, listD);
	pri(listD);

	listD.insertByVal(6);
	pri(listD);
	listD.insertByVal(0);
	pri(listD);
	listD.insertByVal(8);
	pri(listD);

	listD.deleteElemByVal(1);
	pri(listD);
	listD.deleteElemByVal(6);
	pri(listD);
}