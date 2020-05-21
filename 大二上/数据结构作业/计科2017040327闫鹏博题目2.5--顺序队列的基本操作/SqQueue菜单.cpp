#include "SqQueue.h"
using namespace std;

void menu();

int main() {
	menu();
	int opeNum;
	int tempElem, memNum;
	SqQueue<int> queueA;
	while (cout << "请输入操作数:" && cin >> opeNum && opeNum != 0) {
		switch (opeNum) {
		case 1:
			cout << "请输入队内元素总数" << endl;
			cin >> memNum;
			for (int i = 0; i < memNum; i++) {
				cout << "请输入队内元素:" << endl;
				cin >> tempElem;
				queueA.inQueue(tempElem);
			}
			break;
		case 2:
			cout << "队长为" << queueA.getLength() << endl;
			break;
		case 3:
			cout << "请输入要入队元素" << endl;
			cin >> tempElem;
			queueA.inQueue(tempElem);
			break;
		case 4:
			queueA.outQueue(tempElem);
			cout << "出队元素为" << tempElem << endl;
			break;
		case 5:
			if (queueA.isEmpty()) cout << "队空" << endl;
			else cout << "队非空" << endl;
			break;
		case 6:
			if (queueA.isFull()) cout << "队满" << endl;
			else cout << "队没满" << endl;
			break;
		case 7:
			queueA.clean();
			break;
		case 8:
			queueA.display();
			break;		
		}
	}
	return 0;
}

void menu() {
	cout << "*************************线性循环队列菜单************************" << endl;
	cout << "1.创建循环队列" << endl;
	cout << "2.求队长" << endl;
	cout << "3.入队" << endl;
	cout << "4.出队" << endl;
	cout << "5.判队空" << endl;
	cout << "6.判队满" << endl;
	cout << "7.将队列清空" << endl;
	cout << "8.显示队内元素" << endl;
}