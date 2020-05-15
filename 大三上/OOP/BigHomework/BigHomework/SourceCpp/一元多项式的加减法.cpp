#include "Polynomial.h"
#include <iostream>
using namespace std;

int main() {
	Polynomial polyA, polyB;
	PolyItem itemA, itemB;
	double coef;
	int expn;
	cout << "********************************************" << endl;
	cout << "提示:输入为两个一元多项式，每个一元多项式输入一行，按照降幂依次";
	cout << "输入每个单项式的系数和指数，并以-1 -1作为结束。系数和指数均为整数，指数不小于0。";
	cout << endl;

	while (cin >> coef >> expn && expn != -1) {
		itemA.mCoef = coef;
		itemA.mExpn = expn;
		polyA.insert(itemA);
	}

	while (cin >> coef >> expn && expn != -1) {
		itemB.mCoef = coef;
		itemB.mExpn = expn;
		polyB.insert(itemB);
	}

	cout << "1.对两个多项式进行加法运算" << endl;
	cout << "2.对两个多项式进行减法运算" << endl;

	int opeNum;
	cin >> opeNum;
	Polynomial polyC;
	switch (opeNum) {
	case 1:
		polyC = polyA + polyB;
		polyC.display();
		break;
	case 2:
		polyC = polyA - polyB;
		polyC.display();
		break;
	default:
		break;
	}
	return 0;

}