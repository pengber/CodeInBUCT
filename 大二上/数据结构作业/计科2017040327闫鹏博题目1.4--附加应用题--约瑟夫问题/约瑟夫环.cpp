#include "CircleLinkList.h"
#include "PolyItem.h"
using namespace std;

void display(CircleLinkList<int> & cList) {
for (int i = 1; i <= cList.getLength(); i++) {
	int tempElem;
	cList.getElem(i, tempElem);
	cout << tempElem << endl;
	}
}

int main() {
	CircleLinkList<PolyItem> cListA;
	PolyItem item[100];
	int i = 1, num;
	double coef, expn;
	cout << "请输入总人数" << endl;
	cin >> num;
	cout << "请输入第i个人和它所对应的密码,例如:" << endl;
	cout << "1 3 2 3 3 3 4 3 5 3 6 3 7 3 8 3" << endl;
	for (int i = 1; i <= num; i++) {
		cin >> coef >> expn;
		item[i].mCoef = coef;
		item[i].mExpn = expn;
	}
	cListA.setElem(1, item[1]);

	for (int i = 2; i <= num; i++) {
		cListA.insert(i, item[i]);
	}
	cListA.ysfCircle();

	return 0;
	
}