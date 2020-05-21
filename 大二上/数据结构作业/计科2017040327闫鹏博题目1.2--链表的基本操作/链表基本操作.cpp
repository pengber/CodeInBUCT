#include "LinkList.h"
using namespace std;

int main() {
	cout << "**********************菜单*******************" << endl;
	cout << "1.头插法建立链表" << endl;
	cout << "2.尾插法建立链表" << endl;
	cout << "3.求链表长度" << endl;
	cout << "4.判断链表是否为空" << endl;
	cout << "5.清空链表" << endl;
	cout << "6.定位元素" << endl;
	cout << "7.求某个位置元素值" << endl;
	cout << "8.重置某位置元素值" << endl;
	cout << "9.删除某个位置上元素" << endl;
	cout << "10.删除某个元素" << endl;
	cout << "11.在某位置插入元素" << endl;
	cout << "12.插入某元素(按值插)" << endl;
	cout << "13.在表头插入某元素" << endl;
	cout << "14.在表尾插入某元素" << endl;
	cout << "15.打印链表信息" << endl;
	cout << "********************************************" << endl;
	int tempElem;
	int tempPos;
	int opeNum, elemNum;
	LinkList<int> linkList;
	while (cout << "请输入操作序号:" << endl && cin >> opeNum) {
		switch (opeNum) {
		case(1): {
			cout << "请输入要插入的元素个数" << endl;
			cin >> elemNum;
			for (int i = 1; i <= elemNum; i++) {
				cin >> tempElem;
				linkList.insertElemBeforeALL(tempElem);
			}
			break;
		}
		case(2): {
			cout << "请输入要插入的元素个数" << endl;
			cin >> elemNum;
			for (int i = 1; i <= elemNum; i++) {
				cin >> tempElem;
				linkList.insertElemBehindAll(tempElem);
			}
			break;
		}
		case(3): {
			cout << "链表长度为" << linkList.getLength() << endl;
			break;
		}
		case(4): {
			if (linkList.isEmpty()) cout << "链表为空" << endl;
			else cout << "链表不为空" << endl;
			break;
		}
		case(5): {
			linkList.clear();
			break;
		}
		case(6): {
			cout << "请输入需要定位元素的值" << endl;
			cin >> tempElem;
			if (linkList.locateElem(tempElem)) cout << "元素在第" << linkList.locateElem(tempElem) << "位置上" << endl;
			else cout << "无此元素" << endl;
			break;
		}
		case(7): {
			cout << "请输入位置" << endl;
			cin >> tempPos;
			if (linkList.getElem(tempPos, tempElem)) cout << "此位置元素值为" << tempElem << endl;
			else cout << "位置输入不合法" << endl;
			break;
		}
		case(8): {
			cout << "请输入位置" << endl;
			cin >> tempPos;
			cout << "请输入值" << endl;
			cin >> tempElem;
			linkList.setElem(tempPos, tempElem);
			break;
		}
		case(9): {
			cout << "请输入位置" << endl;
			cin >> tempPos;
			linkList.deleteElem(tempPos);
			break;
		}
		case(10): {
			cout << "请输入值" << endl;
			cin >> tempElem;
			linkList.deleteElemByVal(tempElem);
			break;
		}
		case(11): {
			cout << "请输入位置" << endl;
			cin >> tempPos;
			cout << "请输入值" << endl;
			cin >> tempElem;
			linkList.insertElem(tempPos, tempElem);
			break;
		}
		case(12): {
			cout << "请输入值" << endl;
			cin >> tempElem;
			linkList.insertElemByVal(tempElem);
			break;
		}
		case(13): {
			cout << "请输入值" << endl;
			cin >> tempElem;
			linkList.insertElemBeforeALL(tempElem);
			break;	
		}
		case(14): {
			cout << "请输入值" << endl;
			cin >> tempElem;
			linkList.insertElemBehindAll(tempElem);
			break;
		}
		case(15): {
			linkList.priLinkList();
			break;
		}
		default:
			break;
		}
	}
}