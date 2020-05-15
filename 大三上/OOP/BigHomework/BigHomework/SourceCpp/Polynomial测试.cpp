#include "Polynomial.h"
#include <iostream>
using namespace std;

int main() {
	Polynomial polyA, polyB;
	PolyItem itemA, itemB;
	double coef;
	int expn;

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
	Polynomial polyC;
	polyC = polyA  - polyB;
	polyC.display();
	return 0;
	
}